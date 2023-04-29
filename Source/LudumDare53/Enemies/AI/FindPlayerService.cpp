// Made by TitledGooseTeam during Ludum Dare 53


#include "FindPlayerService.h"

#include "BehaviorTree/BlackboardComponent.h"

UFindPlayerService::UFindPlayerService()
{
	NodeName = "Find Player";
}

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (
		Blackboard &&
		GetWorld() != nullptr &&
		GetWorld()->GetFirstPlayerController() != nullptr &&
		GetWorld()->GetFirstPlayerController()->GetPawn() != nullptr
	)
	{
		Blackboard->SetValueAsObject(PlayerActorKey.SelectedKeyName, GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
