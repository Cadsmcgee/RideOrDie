// UpgradeManagerComponent.cpp
#include "UpgradeManagerComponent.h"

bool UUpgradeManagerComponent::HasUpgrade(EUpgradeId Id) const
{
	return OwnedUpgrades.Contains(Id);
}

void UUpgradeManagerComponent::ApplyUpgrade(EUpgradeId Id, float Value)
{
	// Prevent duplicates if you want (comment out if stackable)
	if (OwnedUpgrades.Contains(Id))
	{
		// If you want stacking, delete this block.
		return;
	}

	switch (Id)
	{
	case EUpgradeId::MaxHealth:
		MaxHealth += Value;
		break;

	case EUpgradeId::Damage:
		Damage += Value;
		break;

	case EUpgradeId::MoveSpeed:
		MoveSpeed += Value;
		break;

	case EUpgradeId::ScoreMultiplier:
		ScoreMultiplier += Value;
		break;

	case EUpgradeId::BuffDuration:
		BuffDurationMultiplier += Value;
		break;

	default:
		break;
	}

	OwnedUpgrades.Add(Id);
	OnUpgradeApplied.Broadcast(Id);
}
