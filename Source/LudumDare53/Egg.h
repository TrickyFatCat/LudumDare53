// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Character.h"
#include "Egg.generated.h"

class UCharacterMovementComponent;
class UEggHitPointsComponent;
class UCapsuleComponent;
class UStaticMeshComponent;
class USphereInteractionComponent;
class UEggManagerComponent;

UCLASS()
class LUDUMDARE53_API AEgg : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AEgg();

	void SetEggManager(UEggManagerComponent* Manager);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UEggHitPointsComponent> HitPoints = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereInteractionComponent> InteractionTrigger = nullptr;

	UPROPERTY()
	TObjectPtr<UEggManagerComponent> EggManager = nullptr;

	virtual bool FinishInteraction_Implementation(AActor* OtherActor) override;


public:
	void ToggleCollision(const bool bIsEnabled) const;
};
