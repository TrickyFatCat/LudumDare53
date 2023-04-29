// Made by TitledGooseTeam during Ludum Dare 53


#include "EnemyController.h"

#include "EnemyCharacter.h"
#include "LudumDare53/Components/EnemyPerceptionComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	EnemyPerceptionComponent = CreateDefaultSubobject<UEnemyPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*EnemyPerceptionComponent);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto Char = Cast<AEnemyCharacter>(InPawn);
	if (Char == nullptr) return;

	RunBehaviorTree(Char->GetBehaviorTree());
}
