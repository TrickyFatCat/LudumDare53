// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "PickupEffectType.h"
#include "MeatPickupEffect.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMDARE53_API UMeatPickupEffect : public UPickupEffectType
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MeatAmount = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bClampToMax = true;
	
	virtual bool ActivateEffect_Implementation(AActor* OtherActor) override;
};
