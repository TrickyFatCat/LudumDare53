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

UCLASS()
class LUDUMDARE53_API AEgg : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AEgg();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UEggHitPointsComponent> HitPoints = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereInteractionComponent> InteractionTrigger = nullptr;

	virtual void StartInteraction_Implementation(AActor* OtherActor) override;
};
