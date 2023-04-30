// Made by TitledGooseTeam during Ludum Dare 53


#include "FindEggService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare53/Egg.h"
#include "LudumDare53/Enemies/EnemyCharacter.h"

UFindEggService::UFindEggService()
{
	NodeName = "Find Egg";
}

void UFindEggService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard && Controller)
	{
		const auto Pawn = Cast<AEnemyCharacter>(Controller->GetPawn());
		if (Pawn)
		{
			const auto Target = Pawn->FindTarget(AEgg::StaticClass());
			Blackboard->SetValueAsObject(EggActorKey.SelectedKeyName, Target);
			if (Target)Blackboard->SetValueAsVector(LocationKey.SelectedKeyName, Target->GetActorLocation());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
