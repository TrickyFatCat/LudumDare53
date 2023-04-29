// Made by TitledGooseTeam during Ludum Dare 53


#include "EnemyCharacter.h"

#include "EnemyController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LudumDare53/Components/HitPointsComponent.h"
#include "LudumDare53/Components/LivesComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AEnemyController::StaticClass();

	HitPointComponent = CreateDefaultSubobject<UHitPointsComponent>("HP");

	if (GetCharacterMovement())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

UBehaviorTree* AEnemyCharacter::GetBehaviorTree()
{
	return BehaviorTreeAsset;
}

void AEnemyCharacter::PlayDeathMontage(AController* DeathInstigator, AActor* DeathCauser, const UDamageType* DamageType)
{
	GetCapsuleComponent()->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetMesh()->SetCollisionResponseToChannels(ECR_Ignore);
	PlayAnimMontage(DeathMontage);
}
