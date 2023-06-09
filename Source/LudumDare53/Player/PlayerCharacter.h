﻿// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UPlayerDeathSequenceComponent;
class USpringArmComponent;
class UCameraComponent;
class UHitPointsComponent;
class ULivesComponent;
class UMeatCounterComponent;
class UInputMappingContext;
class UInputAction;
class UInteractionQueueComponent;
class UEggManagerComponent;
class UStarsCounterComponent;
class UStunComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpStartedSignature);

UCLASS()
class LUDUMDARE53_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	bool bHasHat = false;;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHatChanged(const bool bIsVisible);

public:
	UFUNCTION(BlueprintCallable)
	void ToggleHat(const bool bIsVisible);

	bool GetHasHat() const { return bHasHat; }
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable)
	FOnJumpStartedSignature OnJumpStarted;

private:
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArm = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<UCameraComponent> Camera = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHitPointsComponent> HitPoints = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULivesComponent> LivesComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMeatCounterComponent> MeatCounter = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerDeathSequenceComponent> DeathSequence = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractionQueueComponent> InteractionQueue = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEggManagerComponent> EggManager = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStarsCounterComponent> StarsCounter = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStunComponent> StunComponent = nullptr;
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStunComponent> InvulnerabilityComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	FVector CameraSensitivity{0.f, 25.f, 25.f};

	float DefaultGravityScale = 2.0;

	UPROPERTY(EditAnywhere)
	float GravityScaleDelta = 1.0;

	UPROPERTY(EditAnywhere)
	float ThrowPower = 1250;

	bool bIsEggDestroyed = false;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void DecreaseLives();

	UFUNCTION()
	void HandleMeatCounterIncrease(const int32 NewValue, const int32 Amount);

	UFUNCTION()
	void HandleLivesDecrease(const int32 NewValue, const int32 Amount);

	UFUNCTION()
	void HandleEggDeath();
	
	UFUNCTION()
	void HandleRespawn();

	UFUNCTION()
	void HandleStunStarted();
	
	UFUNCTION()
	void HandleStunFinished();

	UFUNCTION()
	void HandlePause();

	virtual float TakeDamage(float DamageAmount,
	                         FDamageEvent const& DamageEvent,
	                         AController* EventInstigator,
	                         AActor* DamageCauser) override;

	virtual void FellOutOfWorld(const UDamageType& dmgType) override;
	
	void ToggleInput(const bool bIsEnabled);

	void StartInteraction();

	void Throw();

	virtual void Jump() override;

	
};
