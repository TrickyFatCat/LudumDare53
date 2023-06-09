// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "PlayerControllerSession.h"

#include "Kismet/GameplayStatics.h"

APlayerControllerSession::APlayerControllerSession()
{
}

void APlayerControllerSession::BeginPlay()
{
	const UWorld* World = GetWorld();

	if (World)
	{
		AGameModeSession* GameMode = Cast<AGameModeSession>(World->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->OnStateChanged.AddDynamic(this, &APlayerControllerSession::OnGameModeStateChanged);
		}
	}

	bShowMouseCursor = false;
	SetTickableWhenPaused(true);

	Super::BeginPlay();
}

void APlayerControllerSession::OnGameModeStateChanged_Implementation(EGameModeState NewState)
{
	auto ToggleInput = [&](const bool bEnableInput, const bool bShowCursor, const FInputModeDataBase& InputMode)
	{
		bEnableInput ? EnableInput(this) : DisableInput(this);
		bShowMouseCursor = bShowCursor;
		SetInputMode(InputMode);
	};

	switch (NewState)
	{
	case EGameModeState::InProgress:
		ToggleInput(true, bShowCursorOnStart, FInputModeGameOnly());
		break;

	case EGameModeState::Finished:
		ToggleInput(false, false, FInputModeGameOnly());
		break;

	case EGameModeState::GameOver:
		ToggleInput(false, true, FInputModeUIOnly());

	case EGameModeState::Pause:
		ToggleInput(true, true, FInputModeGameAndUI());
		break;

	default:
		ToggleInput(false, false, FInputModeUIOnly());
		break;
	}
}

void APlayerControllerSession::PauseGame()
{
	IsPaused()
		? UGameplayStatics::SetGamePaused(GetWorld(), false)
		: UGameplayStatics::SetGamePaused(GetWorld(), true);
}
