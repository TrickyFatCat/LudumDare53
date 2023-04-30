// Made by TitledGooseTeam during Ludum Dare 53


#include "StarPickupEffect.h"

#include "LudumDare53/Components/StarsCounterComponent.h"

bool UStarPickupEffect::ActivateEffect_Implementation(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
	{
		return false;
	}

	UStarsCounterComponent* StarsCounter = OtherActor->FindComponentByClass<UStarsCounterComponent>();

	if (!StarsCounter)
	{
		return false;
	}

	return StarsCounter->IncreaseValue(StarsAmount, false);
}
