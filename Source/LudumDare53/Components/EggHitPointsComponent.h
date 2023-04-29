// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "HitPointsComponent.h"
#include "EggHitPointsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UEggHitPointsComponent : public UHitPointsComponent
{
	GENERATED_BODY()

public:
	UEggHitPointsComponent();

	UFUNCTION(BlueprintCallable)
	void StartDeathTimer();

	UFUNCTION(BlueprintCallable)
	void StopDeathTimer();

	UFUNCTION(BlueprintPure)
	float GetElapsedTime();
	
	UFUNCTION(BlueprintPure)
	float GetRemainingTime();
	
protected:
	FTimerHandle DeathTimerHandle;

	UPROPERTY(EditAnywhere, meta=(ClampMin = "0.1"))
	float DeathTimerRate = 3.0;

	FTimerManager& GetTimerManager();

	UFUNCTION()
	void DecreaseHitPoints();
};
