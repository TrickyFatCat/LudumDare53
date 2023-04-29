// Made by TitledGooseTeam during Ludum Dare 53

#include "AbilityActivationTask.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare53/Components/AbilityComponent.h"

EBTNodeResult::Type UAbilityActivationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
	if (Controller) {
		const auto Ability = Controller->GetPawn()->FindComponentByClass<UAbilityComponent>();
		if (Ability) HasAim ? Ability->ActivateAbility() : Ability->DeactivateAbility();
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
