// UpgradeManagerComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeTypes.h"
#include "UpgradeManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeApplied, EUpgradeId, UpgradeId);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAM305_GREENTEAM_API UUpgradeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnUpgradeApplied OnUpgradeApplied;

	// Optional: track what’s already taken so you don’t offer repeats.
	UPROPERTY(BlueprintReadOnly)
	TArray<EUpgradeId> OwnedUpgrades;

	// All possible upgrades that can be offered (set in BP defaults)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades|Defs")
	TArray<FUpgradeDef> UpgradePool;

	// Your actual stats (or mirror into your existing variables)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades|Stats")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades|Stats")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades|Stats")
	float MoveSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades|Stats")
	float ScoreMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades|Stats")
	float BuffDurationMultiplier = 1.f;

	UFUNCTION(BlueprintCallable, Category = "Upgrades")
	void ApplyUpgrade(EUpgradeId Id, float Value);

	UFUNCTION(BlueprintCallable, Category = "Upgrades")
	bool HasUpgrade(EUpgradeId Id) const;
};
