// Made by TitledGooseTeam during Ludum Dare 53


#include "EggStart.h"

#include "LudumDare53/Egg.h"


AEggStart::AEggStart()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(GetRootComponent());
}

void AEggStart::BeginPlay()
{
	Super::BeginPlay();

	AEgg* Egg = GetWorld()->SpawnActor<AEgg>(EggClass, SpawnPoint->GetComponentTransform());

	if (Egg)
	{
		Egg->OnEggTaken.AddDynamic(this, &AEggStart::HandleEggTaken);
	}
}

void AEggStart::HandleEggTaken()
{
	OnEggTaken.Broadcast();
}
