#include "WBP_Leaderboard_Cpp.h"

#include "Algo/Sort.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Engine/Engine.h"
#include "UObject/UnrealType.h"

static void Screen(const FString& Msg, float Time = 6.f)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Yellow, Msg);
	}
}

UScriptStruct* UWBP_Leaderboard_Cpp::GetSTEntryStruct()
{
	// Your BP struct asset: /Game/Widgets/ST_LeaderboardEntry
	// If your folder is different, change this path to match.
	static const TCHAR* STPath = TEXT("/Game/Widgets/ST_LeaderboardEntry.ST_LeaderboardEntry");
	static UScriptStruct* Cached = nullptr;

	if (!Cached)
	{
		Cached = FindObject<UScriptStruct>(nullptr, STPath);
		if (!Cached)
		{
			Cached = LoadObject<UScriptStruct>(nullptr, STPath);
		}

		if (!Cached)
		{
			Screen(FString::Printf(TEXT("GetSTEntryStruct FAILED: %s"), STPath));
		}
	}

	return Cached;
}

void UWBP_Leaderboard_Cpp::FillSTEntry(UScriptStruct* Struct, void* Dest, const FLeaderboardRuntimeEntry& Src)
{
	if (!Struct || !Dest)
		return;

	for (FProperty* Prop = Struct->PropertyLink; Prop; Prop = Prop->PropertyLinkNext)
	{
		const FName N = Prop->GetFName();

		// Name (String)
		if (FStrProperty* SP = CastField<FStrProperty>(Prop))
		{
			if (N == "Name")
			{
				SP->SetPropertyValue_InContainer(Dest, Src.Name);
			}
			continue;
		}

		// TimeSeconds, Highscore (Float)
		if (FFloatProperty* FP = CastField<FFloatProperty>(Prop))
		{
			if (N == "TimeSeconds")
			{
				FP->SetPropertyValue_InContainer(Dest, Src.TimeSeconds);
			}
			else if (N == "Highscore")
			{
				FP->SetPropertyValue_InContainer(Dest, Src.Highscore);
			}
			continue;
		}

		// Level (Int)
		if (FIntProperty* IP = CastField<FIntProperty>(Prop))
		{
			if (N == "Level")
			{
				IP->SetPropertyValue_InContainer(Dest, Src.Level);
			}
			continue;
		}
	}
}

void UWBP_Leaderboard_Cpp::RebuildUI(const TArray<FLeaderboardRuntimeEntry>& Entries)
{
	UScriptStruct* STStruct = GetSTEntryStruct();

	// quick sanity
	Screen(FString::Printf(TEXT("RebuildUI CALLED_Entries=%d"), Entries.Num()));
	Screen(FString::Printf(TEXT("RowWidgetClass=%s"), RowWidgetClass ? TEXT("OK") : TEXT("NULL")));
	Screen(FString::Printf(TEXT("RowsBox=%s"), RowsBox ? TEXT("OK") : TEXT("NULL")));
	Screen(FString::Printf(TEXT("STStruct=%s"), STStruct ? TEXT("OK") : TEXT("NULL")));

	if (!RowsBox || !RowWidgetClass)
		return;

	// sort (highscore desc, then time asc)
	TArray<FLeaderboardRuntimeEntry> Working = Entries;
	Algo::Sort(Working, [](const FLeaderboardRuntimeEntry& A, const FLeaderboardRuntimeEntry& B)
		{
			if (A.Highscore != B.Highscore)
				return A.Highscore > B.Highscore;

			return A.TimeSeconds < B.TimeSeconds;
		});

	RowsBox->ClearChildren();

	static const FName SetRowDataName(TEXT("SetRowData"));

	int32 AddedCount = 0;
	int32 CreateFailCount = 0;
	int32 MissingFnCount = 0;
	int32 NoWorldCount = 0;

	for (int32 i = 0; i < Working.Num(); i++)
	{
		UWorld* World = GetWorld();
		if (!World)
		{
			NoWorldCount++;
			break;
		}

		UUserWidget* Row = CreateWidget<UUserWidget>(World, RowWidgetClass);
		if (!Row)
		{
			CreateFailCount++;
			continue;
		}

		// ADD FIRST (proves UI add path works even if SetRowData fails)
		RowsBox->AddChild(Row);
		AddedCount++;

		// OPTIONAL: call BP function SetRowData(Entry, PlaceIn)
		UFunction* Fn = Row->FindFunction(SetRowDataName);
		if (!Fn)
		{
			MissingFnCount++;
			continue;
		}

		uint8* Params = (uint8*)FMemory::Malloc(Fn->ParmsSize);
		FMemory::Memzero(Params, Fn->ParmsSize);

		const int32 PlaceValue = i + 1;

		// Fill parameters by reflection:
		for (FProperty* Prop = Fn->PropertyLink; Prop; Prop = Prop->PropertyLinkNext)
		{
			if (!(Prop->PropertyFlags & CPF_Parm))
				continue;

			// Struct param: ST_LeaderboardEntry
			if (FStructProperty* SP = CastField<FStructProperty>(Prop))
			{
				if (STStruct && SP->Struct == STStruct)
				{
					void* ParamAddr = SP->ContainerPtrToValuePtr<void>(Params);
					FillSTEntry(STStruct, ParamAddr, Working[i]);
				}
			}
			// Int param: Place / PlaceIn
			else if (FIntProperty* IP = CastField<FIntProperty>(Prop))
			{
				const FName PN = Prop->GetFName();
				if (PN == "Place" || PN == "PlaceIn")
				{
					IP->SetPropertyValue_InContainer(Params, PlaceValue);
				}
			}
		}

		Row->ProcessEvent(Fn, Params);

		// cleanup param storage
		for (FProperty* Prop = Fn->PropertyLink; Prop; Prop = Prop->PropertyLinkNext)
		{
			if (Prop->PropertyFlags & CPF_Parm)
				Prop->DestroyValue_InContainer(Params);
		}

		FMemory::Free(Params);
	}

	Screen(FString::Printf(TEXT("RebuildUI DONE. Added=%d CreateFail=%d MissingFn=%d NoWorld=%d"),
		AddedCount, CreateFailCount, MissingFnCount, NoWorldCount));
}
