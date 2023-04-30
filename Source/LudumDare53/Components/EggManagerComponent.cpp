// Made by TitledGooseTeam during Ludum Dare 53


#include "EggManagerComponent.h"

#include "LudumDare53/Egg.h"


UEggManagerComponent::UEggManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UEggManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	TargetMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}

void UEggManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEggManagerComponent::ThrowEgg()
{
	if (!IsValid(Egg))
	{
		return;
	}

	Egg->Throw(FVector{0.0, 0.0, 1000.0});
	Egg = nullptr;
}

void UEggManagerComponent::SetEgg(AEgg* NewEgg)
{
	if (Egg || !IsValid(NewEgg))
	{
		return;
	}

	Egg = NewEgg;
}
