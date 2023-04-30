// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AbilityActivationService.generated.h"

UCLASS()
class LUDUMDARE53_API UAbilityActivationService : public UBTService
{
	GENERATED_BODY()

public:
	UAbilityActivationService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector PlayerActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TSubclassOf<UActorComponent> AbilityClass;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
