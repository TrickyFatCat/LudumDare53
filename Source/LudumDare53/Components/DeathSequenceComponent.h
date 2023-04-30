// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeathSequenceComponent.generated.h"

class UAnimMontage;
class ACharacter;
class UAnimInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSequenceStartedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSequenceFinishedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UDeathSequenceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDeathSequenceComponent();

	UPROPERTY(BlueprintAssignable)
	FOnDeathSequenceStartedSignature OnDeathSequenceStarted;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSequenceFinishedSignature OnDeathSequenceFinished;
	
	UFUNCTION()
	void StartDeathSequence(const bool bEggIsDead = false);
	
protected:
	virtual void InitializeComponent() override;
	 
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> EggDeathAnimation;
	
	UPROPERTY()
	ACharacter* Character = nullptr;

	UPROPERTY()
	UAnimInstance* AnimInstance = nullptr;

	UFUNCTION()
	void FinishDeathSequence(UAnimMontage* AnimMontage, const bool bIsInterrupted);

	virtual void HandleDeathSequenceFinish();
};
