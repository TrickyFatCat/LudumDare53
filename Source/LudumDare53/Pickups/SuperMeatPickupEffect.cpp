// Made by TitledGooseTeam during Ludum Dare 53


#include "SuperMeatPickupEffect.h"

#include "LudumDare53/Components/MeatCounterComponent.h"

bool USuperMeatPickupEffect::ActivateEffect_Implementation(AActor* OtherActor)
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

	const int32 Amount = MeatCounter->GetMaxValue() - MeatCounter->GetValue() + 3;
	return MeatCounter->IncreaseValue(Amount, false);
}
