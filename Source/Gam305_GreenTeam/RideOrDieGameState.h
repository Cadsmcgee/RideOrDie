#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LeaderboardRuntimeTypes.h"
#include "RideOrDieGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeaderboardChanged);

UCLASS()
class GAM305_GREENTEAM_API ARideOrDieGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    TArray<FLeaderboardRuntimeEntry> Leaderboard;

    UPROPERTY(BlueprintAssignable)
    FOnLeaderboardChanged OnLeaderboardChanged;

    UFUNCTION(BlueprintCallable)
    void SubmitRun(const FString& Name, float TimeSeconds, float Highscore, int32 Level);

    UFUNCTION(BlueprintCallable)
    const TArray<FLeaderboardRuntimeEntry>& GetLeaderboard() const;

private:
    void LoadLeaderboard();
    void SaveLeaderboard();
    void SortLeaderboard();

    static constexpr int32 MaxEntries = 25;
    static const FString SaveSlot;
};
