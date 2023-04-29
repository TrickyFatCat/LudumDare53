// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;	
class UHitPointsComponent;
class ULivesComponent;
class UMeatCounterComponent;

UCLASS()
class LUDUMDARE53_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArm = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<UCameraComponent> Camera = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<UHitPointsComponent> HitPoints = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<ULivesComponent> LivesComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<UMeatCounterComponent> MeatCounterComponent = nullptr;

	UFUNCTION()
	void DecreaseLives();

	UFUNCTION()
	void HandleMeatCounterIncrease(const int32 NewValue, const int32 Amount);
};

