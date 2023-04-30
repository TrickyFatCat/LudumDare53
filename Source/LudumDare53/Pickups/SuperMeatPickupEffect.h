// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "PickupEffectType.h"
#include "SuperMeatPickupEffect.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMDARE53_API USuperMeatPickupEffect : public UPickupEffectType
{
	GENERATED_BODY()

protected:
	virtual bool ActivateEffect_Implementation(AActor* OtherActor) override;
};
