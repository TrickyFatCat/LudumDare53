// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "FinishMenuWidget.generated.h"

class UButtonWidget;
class UTransitionScreenWidget;

/**
 * A widget for creation of a simple finish menu.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API UFinishMenuWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FinishScreen", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Continue = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FinishScreen", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Restart = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FinishScreen", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Quit = nullptr;

	UPROPERTY()
	TObjectPtr<UButtonWidget> ClickedButton = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FinishScreen", meta=(BindWidget))
	TObjectPtr<UTransitionScreenWidget> Widget_TransitionScreen = nullptr;

	/**Called when any button clicked.*/
	UFUNCTION(BlueprintNativeEvent, Category="FinishScreen")
	void OnButtonClicked(UButtonWidget* Button);

	virtual void OnButtonClicked_Implementation(UButtonWidget* Button);

	/**
	 *Called when Button_Continue is clicked.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="FinishScreen")
	void Continue();

	virtual void Continue_Implementation();

	/**
	 *Reloads current level. 
	 *Called when the transition screen were showed after click on Button_Restart.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="FinishScreen")
	void Restart();

	virtual void Restart_Implementation();

	/**
	 *Quits the game.
	 *Called when the transition screen were showed after click on Button_Quit.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="FinishScreen")
	void Quit();

	virtual void Quit_Implementation();

	/**
	 *Called when the transition screen finishes its show animation.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="FinishScreen")
	void OnTransitionScreenShowed();

	virtual void OnTransitionScreenShowed_Implementation();
};
