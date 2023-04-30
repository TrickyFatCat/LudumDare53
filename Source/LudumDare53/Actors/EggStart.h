// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LudumDare53/Egg.h"
#include "EggStart.generated.h"

class AEgg;
class USceneComponent;

UCLASS()
class LUDUMDARE53_API AEggStart : public AActor
{
	GENERATED_BODY()

public:
	AEggStart();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnEggTakenSignature OnEggTaken;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SpawnPoint = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AEgg> EggClass = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void OnEggWasTaken();
	
	UFUNCTION()
	void HandleEggTaken();
};
