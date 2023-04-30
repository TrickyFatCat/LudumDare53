// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "PickupEffectType.h"
#include "StarPickupEffect.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMDARE53_API UStarPickupEffect : public UPickupEffectType
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	int32 StarsAmount = 1;

	virtual bool ActivateEffect_Implementation(AActor* OtherActor) override;
};
