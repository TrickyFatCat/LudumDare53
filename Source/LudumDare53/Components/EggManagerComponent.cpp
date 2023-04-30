// Made by TitledGooseTeam during Ludum Dare 53


#include "EggManagerComponent.h"

#include "LudumDare53/Egg.h"


UEggManagerComponent::UEggManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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

void UEggManagerComponent::ThrowEgg(const FVector& Direction, const float Power)
{
	if (!bIsEggInHands || !IsValid(Egg))
	{
		return;
	}
	
	Egg->Throw(Direction, Power);
	bIsEggInHands = false;
}

void UEggManagerComponent::SetEgg(AEgg* NewEgg)
{
	if (Egg || !IsValid(NewEgg))
	{
		return;
	}

	Egg = NewEgg;
}
