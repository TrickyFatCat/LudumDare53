// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StunComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStunStartedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStunFinishedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UStunComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStunComponent();

	UPROPERTY(BlueprintAssignable)
	FOnStunStartedSignature OnStunStarted;
	
	UPROPERTY(BlueprintAssignable)
	FOnStunFinishedSignature OnStunFinished;

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION()
	bool ApplyStun();

	UFUNCTION()
	void StopStun();

	UFUNCTION(BlueprintPure)
	bool GetIsStunned() const { return bIsStunned; }
	
	UPROPERTY(EditAnywhere)
	float StunPower = 800.f;

	UPROPERTY(EditAnywhere)
	float ThrowPower = 800.f;
protected:
	bool bIsStunned = false;

	UPROPERTY(EditAnywhere)
	float StunTime = 0.5f;


	FTimerHandle StunTimerHandle;

	UFUNCTION()
	void FinishStun();
};
