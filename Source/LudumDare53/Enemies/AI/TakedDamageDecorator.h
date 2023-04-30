// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TakedDamageDecorator.generated.h"

UCLASS()
class LUDUMDARE53_API UTakedDamageDecorator : public UBTDecorator
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector TakeDamageKey;
};
