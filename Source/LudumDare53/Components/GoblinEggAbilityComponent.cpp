// Made by TitledGooseTeam during Ludum Dare 53


#include "GoblinEggAbilityComponent.h"

#include "EggManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LudumDare53/Egg.h"

bool UGoblinEggAbilityComponent::ActivateAbility()
{
	if (bIsActivated) return false;

	TArray<AActor*> Actors;
	GetOwner()->GetOverlappingActors(Actors, AEgg::StaticClass());
	if (Actors.IsEmpty()) return false;
	const auto Egg = Cast<AEgg>(Actors[0]);

	Egg->Attach(GetOwner());

	const auto EggManager = GetOwner()->FindComponentByClass<UEggManagerComponent>();
	EggManager->bIsEggInHands = true;
	EggManager->SetEgg(Egg);

	const auto Component = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
	PreviousSpeed = Component->MaxWalkSpeed;
	Component->MaxWalkSpeed = SpeedWithEgg;

	Egg->OnEggTaken.Broadcast();

	bIsActivated = true;
	OnAbilityActivated.Broadcast();
	return true;
}

bool UGoblinEggAbilityComponent::DeactivateAbility()
{
	if (!bIsActivated) return false;

	const auto EggManager = GetOwner()->FindComponentByClass<UEggManagerComponent>();
	EggManager->ThrowEgg(FVector::ZeroVector, 1000);

	const auto Component = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
	Component->MaxWalkSpeed = PreviousSpeed;

	bIsActivated = false;
	OnAbilityDeactivated.Broadcast();
	return true;
}
