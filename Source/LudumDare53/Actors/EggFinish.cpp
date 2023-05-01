// Made by TitledGooseTeam during Ludum Dare 53


#include "EggFinish.h"

#include "BoxInteractionComponent.h"
#include "../Egg.h"
#include "LudumDare53/Components/EggManagerComponent.h"


AEggFinish::AEggFinish()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	EggPoint = CreateDefaultSubobject<USceneComponent>("EggPoint");
	EggPoint->SetupAttachment(GetRootComponent());
	
	InteractionTrigger = CreateDefaultSubobject<UBoxInteractionComponent>("InteractionTrigger");
	InteractionTrigger->SetupAttachment(GetRootComponent());
}

void AEggFinish::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AEggFinish::FinishInteraction_Implementation(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
	{
		return false;
	}

	UEggManagerComponent* EggManager = OtherActor->FindComponentByClass<UEggManagerComponent>();

	if (!EggManager || !EggManager->bIsEggInHands)
	{
		return false;
	}

	AEgg* Egg = EggManager->GetEgg();
	EggManager->bIsEggInHands = false;
	Egg->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Egg->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Egg->SetActorLocation(EggPoint->GetComponentLocation());
	InteractionTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OnEggPlaced.Broadcast();
	OnEggWasPlaced();
	return true;
}
