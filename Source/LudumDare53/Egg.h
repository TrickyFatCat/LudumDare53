﻿// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Egg.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEggTakenSignature);

class UProjectileMovementComponent;
class UEggHitPointsComponent;
class UCapsuleComponent;
class UStaticMeshComponent;
class USphereInteractionComponent;
class UEggManagerComponent;

UCLASS()
class LUDUMDARE53_API AEgg : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AEgg();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UProjectileMovementComponent> MovementComponent = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UEggHitPointsComponent> HitPoints = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereInteractionComponent> InteractionTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	FName SocketName = NAME_None;

	virtual bool FinishInteraction_Implementation(AActor* OtherActor) override;

	void ToggleCollision(const bool bIsEnabled) const;

	void Attach(const AActor* OtherActor);

public:
	UPROPERTY(BlueprintAssignable)
	FOnEggTakenSignature OnEggTaken;

	UFUNCTION(BlueprintCallable)
	void Throw(const FVector& Direction, const float Power);
};