// Made by TitledGooseTeam during Ludum Dare 53


#include "DeathSequenceComponent.h"

#include "GameFramework/Character.h"


UDeathSequenceComponent::UDeathSequenceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


void UDeathSequenceComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Character = Cast<ACharacter>(GetOwner());

	if (Character)
	{
		AnimInstance = Character->GetMesh()->GetAnimInstance();
	
		if (AnimInstance)
		{
			AnimInstance->OnMontageBlendingOut.AddDynamic(this, &UDeathSequenceComponent::FinishDeathSequence);
		}
	}
}

void UDeathSequenceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDeathSequenceComponent::StartDeathSequence()
{
	if (!DeathAnimation || !IsValid(Character))
	{
		return;
	}

	Character->PlayAnimMontage(DeathAnimation);
	OnDeathSequenceStarted.Broadcast();
}

void UDeathSequenceComponent::FinishDeathSequence(UAnimMontage* AnimMontage, const bool bIsInterrupted)
{
	if (AnimMontage != DeathAnimation)
	{
		return;
	}

	HandleDeathSequenceFinish();
	OnDeathSequenceFinished.Broadcast();
}

void UDeathSequenceComponent::HandleDeathSequenceFinish()
{
}
