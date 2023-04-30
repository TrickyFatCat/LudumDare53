// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindPlayerService.generated.h"

UCLASS()
class LUDUMDARE53_API UFindPlayerService : public UBTService
{
	GENERATED_BODY()

public:
	UFindPlayerService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector PlayerActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector LocationKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
