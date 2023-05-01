// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityActivatedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityDeactivatedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityComponent();

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnAbilityActivatedSignature OnAbilityActivated;

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnAbilityDeactivatedSignature OnAbilityDeactivated;

	UFUNCTION(BlueprintCallable, Category="Ability")
	virtual bool ActivateAbility();

	UFUNCTION(BlueprintCallable, Category="Ability")
	virtual bool DeactivateAbility();

protected:
	UPROPERTY(BlueprintReadOnly, Category="Ability")
	bool bIsActivated = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	float CooldownDuration = 0.f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle CooldownTimerHandle;

private:
	UFUNCTION()
	void FinishCooldown();
};
