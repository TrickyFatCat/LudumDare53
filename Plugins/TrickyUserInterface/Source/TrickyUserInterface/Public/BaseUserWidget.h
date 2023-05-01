// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHiddenSignature);

UENUM(BlueprintType)
enum class ETimeFormat : uint8
{
	MM_SS_MsMs UMETA(DisplayName="MM:SS.MsMs"),
	MM_SS_Ms UMETA(DisplayName="MM:SS.Ms"),
	MM_SS UMETA(DisplayName="MM:SS"),
	SS_MsMs UMETA(DisplayName="SS.MsMs"),
	SS_Ms UMETA(DisplayName="SS.Ms"),
	SS UMETA(DisplayName="SS")
};

/**
 * Base user widget.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	/**Starts the show animation.*/
	UFUNCTION(BlueprintCallable, Category="BaseUserWidget")
	void Show();

	/**Starts the hide animation.*/
	UFUNCTION(BlueprintCallable, Category="BaseUserWidget")
	void Hide();

	/**Called when the show animation finishes.*/
	UPROPERTY(BlueprintAssignable, Category="Animation")
	FOnShowedSignature OnShowed;

	/**Called when the hide animation finishes.*/
	UPROPERTY(BlueprintAssignable, Category="Animation")
	FOnHiddenSignature OnHidden;

	UFUNCTION(BlueprintPure)
	static FString ConvertTimeSeconds(const float TimeSeconds, const ETimeFormat TimeFormat);

protected:
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ShowAnimation = nullptr;
	
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> HideAnimation = nullptr;

	virtual void OnAnimationStarted_Implementation(const UWidgetAnimation* Animation) override;
	
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
	
	float CalculateStartTime(const UWidgetAnimation* CurrentAnimation, const UWidgetAnimation* NewAnimation) const;
};
