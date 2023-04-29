// Made by TitledGooseTeam during Ludum Dare 53


#include "PlayerDeathSequenceComponent.h"


UPlayerDeathSequenceComponent::UPlayerDeathSequenceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPlayerDeathSequenceComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UPlayerDeathSequenceComponent::HandleDeathSequenceFinish()
{
	Super::HandleDeathSequenceFinish();
}
