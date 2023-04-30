// Made by TitledGooseTeam during Ludum Dare 53


#include "StunComponent.h"


UStunComponent::UStunComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UStunComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UStunComponent::ApplyStun()
{
	if (bIsStunned)
	{
		return false;
	}
	
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(StunTimerHandle, this, &UStunComponent::FinishStun, StunTime, false);
	OnStunStarted.Broadcast();
	return true;
}

void UStunComponent::StopStun()
{
	if (!bIsStunned)
	{
		return;
	}
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	TimerManager.ClearTimer(StunTimerHandle);
}

void UStunComponent::FinishStun()
{
	bIsStunned = false;
	OnStunFinished.Broadcast();
}
