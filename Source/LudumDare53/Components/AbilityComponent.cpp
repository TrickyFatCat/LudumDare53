// Made by TitledGooseTeam during Ludum Dare 53

#include "AbilityComponent.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UAbilityComponent::ActivateAbility()
{
	if (bIsActivated) return false;

	if (CooldownDuration > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			CooldownTimerHandle,
			this,
			&UAbilityComponent::FinishCooldown,
			CooldownDuration,
			false
		);
	}

	bIsActivated = true;
	OnAbilityActivated.Broadcast();
	return true;
}

void UAbilityComponent::FinishCooldown()
{
	DeactivateAbility();
}

bool UAbilityComponent::DeactivateAbility()
{
	if (!bIsActivated) return false;

	bIsActivated = false;
	OnAbilityDeactivated.Broadcast();
	return true;
}
