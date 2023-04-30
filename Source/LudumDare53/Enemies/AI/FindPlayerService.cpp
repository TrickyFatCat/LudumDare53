// Made by TitledGooseTeam during Ludum Dare 53


#include "FindPlayerService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare53/Enemies/EnemyCharacter.h"

UFindPlayerService::UFindPlayerService()
{
	NodeName = "Find Player";
}

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard && Controller)
	{
		const auto Enemy = Cast<AEnemyCharacter>(Controller->GetPawn());
		if (Enemy) Blackboard->SetValueAsObject(PlayerActorKey.SelectedKeyName, Enemy->Target());
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
