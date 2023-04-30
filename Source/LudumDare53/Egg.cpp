// Made by TitledGooseTeam during Ludum Dare 53


#include "Egg.h"

#include "SphereInteractionComponent.h"
#include "Components/EggHitPointsComponent.h"
#include "Components/EggManagerComponent.h"


AEgg::AEgg()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPoints = CreateDefaultSubobject<UEggHitPointsComponent>("HitPoints");
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	InteractionTrigger = CreateDefaultSubobject<USphereInteractionComponent>("InteractionTrigger");
	InteractionTrigger->SetupAttachment(GetRootComponent());
	InteractionTrigger->SetInteractionMessage(this, "Pickup");
}

void AEgg::SetEggManager(UEggManagerComponent* Manager)
{
	EggManager = Manager;
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

	EggManager->AttachEgg();
	return true;
}

void AEgg::ToggleCollision(const bool bIsEnabled) const
{
	const ECollisionEnabled::Type CollisionEnabled = bIsEnabled
		                                                 ? ECollisionEnabled::QueryAndPhysics
		                                                 : ECollisionEnabled::NoCollision;
	GetMesh()->SetCollisionEnabled(CollisionEnabled);
	InteractionTrigger->SetCollisionEnabled(CollisionEnabled);
}
