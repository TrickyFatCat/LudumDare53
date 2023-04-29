// Made by TitledGooseTeam during Ludum Dare 53


#include "EnemyCharacter.h"

#include "BrainComponent.h"
#include "EnemyController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LudumDare53/Components/DeathSequenceComponent.h"
#include "LudumDare53/Components/HitPointsComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AEnemyController::StaticClass();

	HitPointComponent = CreateDefaultSubobject<UHitPointsComponent>("HP");
	DeathSequenceComponent = CreateDefaultSubobject<UDeathSequenceComponent>("DeathSequence");

	if (GetCharacterMovement())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	HitPointComponent->OnValueZero.AddDynamic(this, &AEnemyCharacter::Die);
}

void AEnemyCharacter::Die()
{
	if (const auto AIController = Cast<AEnemyController>(GetController())) AIController->BrainComponent->Cleanup();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DeathSequenceComponent->StartDeathSequence();
}

float AEnemyCharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	HitPointComponent->DecreaseValue(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
