// Made by TitledGooseTeam during Ludum Dare 53


#include "EnemyCharacter.h"

#include "BrainComponent.h"
#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
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
	SightComponent = CreateDefaultSubobject<USphereComponent>("Sight");
	SightComponent->SetupAttachment(GetRootComponent());

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

AActor* AEnemyCharacter::Target() const
{
	TArray<AActor*> FindActors;
	SightComponent->GetOverlappingActors(FindActors, APlayerCharacter::StaticClass());
	return FindActors.IsEmpty() ? nullptr : FindActors[0];
}

void AEnemyCharacter::Die()
{
	if (const auto AIController = Cast<AEnemyController>(GetController())) AIController->BrainComponent->Cleanup();
	
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
