// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "DeathSequenceComponent.h"
#include "PlayerDeathSequenceComponent.generated.h"

class UTransitionScreenWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRespawnFinishedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UPlayerDeathSequenceComponent : public UDeathSequenceComponent
{
	GENERATED_BODY()

public:
	UPlayerDeathSequenceComponent();

	UPROPERTY(BlueprintAssignable)
	FOnRespawnFinishedSignature OnRespawnFinished;

	bool GetIsGameOver() const { return bIsGameOver; }

	void SetIsGameOver(const bool Value) { bIsGameOver = Value; }

protected:
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

	virtual void HandleDeathSequenceFinish() override;

	UPROPERTY(EditDefaultsOnly, Category="Character")
	TSubclassOf<UTransitionScreenWidget> TransitionWidgetClass = nullptr;

	UPROPERTY()
	UTransitionScreenWidget* TransitionScreenWidget = nullptr;

	UPROPERTY(BlueprintReadOnly)
	bool bIsGameOver = false;

private:
	FTransform InitialTransform;

	UFUNCTION()
	void FinishRestart();
};
