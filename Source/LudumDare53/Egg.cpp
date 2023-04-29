// Made by TitledGooseTeam during Ludum Dare 53


#include "Egg.h"

#include "SphereInteractionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/EggHitPointsComponent.h"


AEgg::AEgg()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPoints = CreateDefaultSubobject<UEggHitPointsComponent>("HitPoints");

	InteractionTrigger = CreateDefaultSubobject<USphereInteractionComponent>("InteractionTrigger");
	InteractionTrigger->SetupAttachment(GetRootComponent());
	InteractionTrigger->SetInteractionMessage(this, "Pickup");

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

}

void AEgg::BeginPlay()
{
	Super::BeginPlay();
}

void AEgg::StartInteraction_Implementation(AActor* OtherActor)
{
}
