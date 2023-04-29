// Made by TitledGooseTeam during Ludum Dare 53


#include "EnemyController.h"

#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare53/Components/EnemyPerceptionComponent.h"
#include "LudumDare53/Components/LivesComponent.h"
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

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetFocus(GetFocusOnActor());
}

AActor* AEnemyController::GetFocusOnActor() const
{
	if (GetPawn()->FindComponentByClass<ULivesComponent>()->GetValue() == 0) return nullptr;
	if (GetBlackboardComponent() == nullptr) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
