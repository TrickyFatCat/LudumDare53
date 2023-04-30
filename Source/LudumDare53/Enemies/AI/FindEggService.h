// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindEggService.generated.h"

UCLASS()
class LUDUMDARE53_API UFindEggService : public UBTService
{
	GENERATED_BODY()

public:
	UFindEggService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector EggActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector LocationKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
