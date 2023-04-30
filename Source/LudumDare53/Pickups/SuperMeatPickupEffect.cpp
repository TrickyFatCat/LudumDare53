// Made by TitledGooseTeam during Ludum Dare 53


#include "SuperMeatPickupEffect.h"

#include "LudumDare53/Components/HitPointsComponent.h"


bool USuperMeatPickupEffect::ActivateEffect_Implementation(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
	{
		return false;
	}

	UHitPointsComponent* HitPointsComponent = OtherActor->FindComponentByClass<UHitPointsComponent>();

	if (!HitPointsComponent)
	{
		return false;
	}

	const int32 Amount = HitPointsComponent->GetMaxValue() - HitPointsComponent->GetValue() + 3;
	return HitPointsComponent->IncreaseValue(Amount, false);
}
