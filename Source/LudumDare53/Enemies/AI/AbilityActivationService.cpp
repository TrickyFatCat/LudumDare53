// Made by TitledGooseTeam during Ludum Dare 53


#include "AbilityActivationService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare53/Components/AbilityComponent.h"
#include "LudumDare53/Enemies/EnemyCharacter.h"

UAbilityActivationService::UAbilityActivationService()
{
	NodeName = "Find Player";
}

void UAbilityActivationService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
	if (Controller)
	{
		const auto Component = Controller->GetPawn()->FindComponentByClass(AbilityClass);
		const auto Ability = Cast<UAbilityComponent>(Component);
		if (Ability) HasAim ? Ability->ActivateAbility() : Ability->DeactivateAbility();
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
