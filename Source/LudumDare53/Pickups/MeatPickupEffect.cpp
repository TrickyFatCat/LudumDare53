// Made by TitledGooseTeam during Ludum Dare 53


#include "MeatPickupEffect.h"

#include "LudumDare53/Components/MeatCounterComponent.h"

bool UMeatPickupEffect::ActivateEffect_Implementation(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
	{
		return false;
	}

	UMeatCounterComponent* MeatCounter = OtherActor->FindComponentByClass<UMeatCounterComponent>();

	if (!MeatCounter)
	{
		return false;
	}

	return MeatCounter->IncreaseValue(MeatAmount, bClampToMax);
}
