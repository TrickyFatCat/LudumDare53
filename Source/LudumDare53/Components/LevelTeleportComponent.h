// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelTeleportComponent.generated.h"

class UTransitionScreenWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTeleportationStartedSignatue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API ULevelTeleportComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULevelTeleportComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTransitionScreenWidget> TransitionWidgetClass = nullptr;

	UPROPERTY()
	UTransitionScreenWidget* TransitionScreenWidget = nullptr;

	UFUNCTION()
	void FinishTeleportation();

public:
	UPROPERTY(BlueprintAssignable)
	FOnTeleportationStartedSignatue OnTeleportationStarted;

	UFUNCTION(BlueprintCallable)
	void StartTeleportation();
};
