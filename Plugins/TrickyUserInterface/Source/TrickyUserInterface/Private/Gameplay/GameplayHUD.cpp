// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "Gameplay/GameplayHUD.h"

#include "BaseUserWidget.h"
#include "GameModeSession.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateUserWidget(EGameModeState::Inactive, InactiveStateWidget);
	CreateUserWidget(EGameModeState::Preparation, PreparationScreenWidget);
	CreateUserWidget(EGameModeState::InProgress, GameplayScreenWidget);
	CreateUserWidget(EGameModeState::Pause, PauseScreenWidget);
	CreateUserWidget(EGameModeState::Finished, FinishScreenWidget);

	
	for (const auto WidgetPair : UserWidgets)
	{
		UBaseUserWidget* UserWidget = WidgetPair.Value;

		if (!UserWidget)
		{
			continue;
		}

		UserWidget->AddToViewport();
		UserWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		TObjectPtr<AGameModeSession> GameMode = Cast<AGameModeSession>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->OnStateChanged.AddDynamic(this, &AGameplayHUD::OnGameModeSessionChanged);
		}
	}
}

void AGameplayHUD::OnGameModeSessionChanged(EGameModeState NewState)
{
	if (ActiveWidget)
	{
		ActiveWidget->Hide();
	}

	if (!UserWidgets.Contains(NewState))
	{
		return;
	}

	ActiveWidget = UserWidgets[NewState];
	ActiveWidget->Show();
}

void AGameplayHUD::CreateUserWidget(const EGameModeState State, TSubclassOf<UBaseUserWidget> WidgetClass)
{
	if (!WidgetClass)
	{
		return;
	}

	UserWidgets.Add(State, ToObjectPtr(CreateWidget<UBaseUserWidget>(GetWorld(), WidgetClass)));
}
