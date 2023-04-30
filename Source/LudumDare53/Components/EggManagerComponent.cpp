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

void UEggManagerComponent::ThrowEgg()
{
	if (!IsValid(Egg))
	{
		return;
	}

	FVector Direction = GetOwner()->GetActorUpVector();
	Direction = Direction.RotateAngleAxis(45, GetOwner()->GetActorRightVector());
	Egg->Throw(Direction,ThrowPower);
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
