// Made by TitledGooseTeam during Ludum Dare 53


#include "GoblinEggAbilityComponent.h"

#include "AIController.h"
#include "EggManagerComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LudumDare53/Egg.h"
#include "LudumDare53/Enemies/EnemyCharacter.h"

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

	const auto Controller = Cast<AAIController>(Cast<AEnemyCharacter>(GetOwner())->GetController());
	Controller->GetBlackboardComponent()->SetValueAsBool("EggInHand", true);

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

	const auto Controller = Cast<AAIController>(Cast<AEnemyCharacter>(GetOwner())->GetController());
	Controller->GetBlackboardComponent()->SetValueAsBool("EggInHand", false);

	bIsActivated = false;
	OnAbilityDeactivated.Broadcast();
	return true;
}
