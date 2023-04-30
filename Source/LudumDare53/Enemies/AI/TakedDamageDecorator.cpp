// Made by TitledGooseTeam during Ludum Dare 53


#include "TakedDamageDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UTakedDamageDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	return Blackboard && Blackboard->GetValueAsBool(TakeDamageKey.SelectedKeyName);
}
