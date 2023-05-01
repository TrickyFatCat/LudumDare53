// Made by TitledGooseTeam during Ludum Dare 53


#include "PlayerDeathSequenceComponent.h"

#include "TransitionScreenWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"

UPlayerDeathSequenceComponent::UPlayerDeathSequenceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


void UPlayerDeathSequenceComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


void UPlayerDeathSequenceComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialTransform = GetOwner()->GetActorTransform();

	if (TransitionWidgetClass)
	{
		TransitionScreenWidget = CreateWidget<UTransitionScreenWidget>(GetWorld(), TransitionWidgetClass);
		TransitionScreenWidget->AddToViewport(-1);
		TransitionScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		TransitionScreenWidget->OnShowed.AddDynamic(this, &UPlayerDeathSequenceComponent::FinishRestart);
	}
}

void UPlayerDeathSequenceComponent::HandleDeathSequenceFinish()
{
	Super::HandleDeathSequenceFinish();

	if (!TransitionScreenWidget)
	{
		return;
	}

	TransitionScreenWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	TransitionScreenWidget->Show();
}


void UPlayerDeathSequenceComponent::FinishRestart()
{
	OnRespawnFinished.Broadcast();

	if (!bIsGameOver)
	{
		TransitionScreenWidget->Hide();
	}
}
