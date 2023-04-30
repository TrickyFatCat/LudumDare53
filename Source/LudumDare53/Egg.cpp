// Made by TitledGooseTeam during Ludum Dare 53


#include "Egg.h"

#include "SphereInteractionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/EggHitPointsComponent.h"
#include "Components/EggManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AEgg::AEgg()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPoints = CreateDefaultSubobject<UEggHitPointsComponent>("HitPoints");
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	InteractionTrigger = CreateDefaultSubobject<USphereInteractionComponent>("InteractionTrigger");
	InteractionTrigger->SetupAttachment(GetRootComponent());
	InteractionTrigger->SetInteractionMessage(this, "Pickup");
}

void AEgg::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool AEgg::FinishInteraction_Implementation(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
	{
		return false;
	}

	UEggManagerComponent* EggManager = OtherActor->FindComponentByClass<UEggManagerComponent>();

	if (!EggManager)
	{
		return false;
	}
	
	Attach(OtherActor, Socket);
	EggManager->SetEgg(this);
	return true;
}

void AEgg::ToggleCollision(const bool bIsEnabled) const
{
	const ECollisionEnabled::Type CollisionEnabled = bIsEnabled
		                                                 ? ECollisionEnabled::QueryAndPhysics
		                                                 : ECollisionEnabled::NoCollision;
	GetCapsuleComponent()->SetCollisionEnabled(CollisionEnabled);
	InteractionTrigger->SetCollisionEnabled(CollisionEnabled);
}

void AEgg::Attach(AActor* OtherActor, const FName& SocketName)
{
	ToggleCollision(false);
	AttachToActor(OtherActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void AEgg::Throw(const FVector& Power)
{
	ToggleCollision(true);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Falling;
	LaunchCharacter(Power, true, true);
}
