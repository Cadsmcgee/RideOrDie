#include "RideOrDieGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SG_LeaderboardSave_Cpp.h"

const FString ARideOrDieGameState::SaveSlot = TEXT("LeaderboardSaveCpp");

void ARideOrDieGameState::BeginPlay()
{
    Super::BeginPlay();
    LoadLeaderboard();
}

const TArray<FLeaderboardRuntimeEntry>& ARideOrDieGameState::GetLeaderboard() const
{
    return Leaderboard;
}

void ARideOrDieGameState::LoadLeaderboard()
{
    if (USaveGame* Raw = UGameplayStatics::LoadGameFromSlot(SaveSlot, 0))
    {
        if (USG_LeaderboardSave_Cpp* Save = Cast<USG_LeaderboardSave_Cpp>(Raw))
        {
            Leaderboard = Save->Entries;
            SortLeaderboard();
            OnLeaderboardChanged.Broadcast();
            return;
        }
    }

    Leaderboard.Reset();
    OnLeaderboardChanged.Broadcast();
}

void ARideOrDieGameState::SaveLeaderboard()
{
    USG_LeaderboardSave_Cpp* Save =
        Cast<USG_LeaderboardSave_Cpp>(UGameplayStatics::CreateSaveGameObject(USG_LeaderboardSave_Cpp::StaticClass()));

    Save->Entries = Leaderboard;
    UGameplayStatics::SaveGameToSlot(Save, SaveSlot, 0);
}

void ARideOrDieGameState::SubmitRun(const FString& Name, float TimeSeconds, float Highscore, int32 Level)
{
    FLeaderboardRuntimeEntry E;
    E.Name = Name;
    E.TimeSeconds = TimeSeconds;
    E.Highscore = Highscore;
    E.Level = Level;

    Leaderboard.Add(E);
    SortLeaderboard();

    if (Leaderboard.Num() > MaxEntries)
    {
        Leaderboard.SetNum(MaxEntries);
    }

    SaveLeaderboard();
    OnLeaderboardChanged.Broadcast();
}

void ARideOrDieGameState::SortLeaderboard()
{
    // Sort by Highscore desc, then TimeSeconds asc, then Level desc (tiebreak)
    Leaderboard.Sort([](const FLeaderboardRuntimeEntry& A, const FLeaderboardRuntimeEntry& B)
        {
            if (A.Highscore != B.Highscore) return A.Highscore > B.Highscore;
            if (A.TimeSeconds != B.TimeSeconds) return A.TimeSeconds < B.TimeSeconds;
            return A.Level > B.Level;
        });
}
