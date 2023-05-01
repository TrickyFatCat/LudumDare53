// Made by TitledGooseTeam during Ludum Dare 53


#include "AIController.h"
#include "CheckDistanceToPlayerDecorator.h"
#include "TakedDamageDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UCheckDistanceToPlayerDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Obj = Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
	if (Obj == nullptr) return false;
	const auto Player = Cast<APawn>(Obj);
	if (Player == nullptr) return false;
	const auto Enemy = OwnerComp.GetAIOwner()->GetInstigatorController()->GetPawn();
	if (Enemy == nullptr) return false;
	auto const DistanceD = FVector::Dist(Enemy->GetActorLocation(), Player->GetActorLocation());
	return DistanceD >= Distance;
}
