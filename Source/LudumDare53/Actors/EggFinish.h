// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "EggFinish.generated.h"

class UBoxInteractionComponent;
class USceneComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEggPlacedSignature);

UCLASS()
class LUDUMDARE53_API AEggFinish : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AEggFinish();

	UPROPERTY(BlueprintAssignable)
	FOnEggPlacedSignature OnEggPlaced;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> EggPoint = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBoxInteractionComponent> InteractionTrigger = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void OnEggWasPlaced();

	virtual bool FinishInteraction_Implementation(AActor* OtherActor) override;
};
