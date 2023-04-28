// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameModeSession.h"
#include "GameplayHUD.generated.h"

class UBaseUserWidget;

/**
 * A base HUD class for gameplay. It automatically show and hide widgets depending on a game state.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	/**A widget which will be shown in the Inactive game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> InactiveStateWidget = nullptr;
	
	/**A widget which will be shown in the Preparation game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> PreparationScreenWidget = nullptr;
	
	/**A widget which will be shown in the InProgress game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> GameplayScreenWidget = nullptr;
	
	/**A widget which will be shown in the Pause game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> PauseScreenWidget = nullptr;
	
	/**A widget which will be shown in the Finished game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> FinishScreenWidget = nullptr;

private:
	UPROPERTY()
	TMap<EGameModeState, TObjectPtr<UBaseUserWidget>> UserWidgets;

	UPROPERTY()
	TObjectPtr<UBaseUserWidget> ActiveWidget = nullptr;

	UFUNCTION()
	void OnGameModeSessionChanged(EGameModeState NewState);
	
	void CreateUserWidget(const EGameModeState State, TSubclassOf<UBaseUserWidget> WidgetClass);
};
