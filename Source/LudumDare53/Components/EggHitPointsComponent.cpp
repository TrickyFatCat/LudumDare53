// Made by TitledGooseTeam during Ludum Dare 53


#include "EggHitPointsComponent.h"


UEggHitPointsComponent::UEggHitPointsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEggHitPointsComponent::StartDeathTimer()
{
	StopDeathTimer();
	FTimerManager& TimerManager = GetTimerManager();

	TimerManager.SetTimer(DeathTimerHandle,
	                      this,
	                      &UEggHitPointsComponent::DecreaseHitPoints,
	                      DeathTimerRate,
	                      true);
}

void UEggHitPointsComponent::StopDeathTimer()
{
	FTimerManager& TimerManager = GetTimerManager();

	TimerManager.ClearTimer(DeathTimerHandle);
}

float UEggHitPointsComponent::GetElapsedTime()
{
	const FTimerManager& TimerManager = GetTimerManager();

	return TimerManager.GetTimerElapsed(DeathTimerHandle);
}

float UEggHitPointsComponent::GetRemainingTime()
{
	const FTimerManager& TimerManager = GetTimerManager();

	return TimerManager.GetTimerRemaining(DeathTimerHandle);
}

FTimerManager& UEggHitPointsComponent::GetTimerManager()
{
	return GetWorld()->GetTimerManager();
}

void UEggHitPointsComponent::DecreaseHitPoints()
{
	DecreaseValue(1);

	if (ResourceData.Value <= 0)
	{
		StopDeathTimer();
	}
}
