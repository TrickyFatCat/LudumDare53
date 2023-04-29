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

	Egg = GetWorld()->SpawnActor<AEgg>(EggClass, FTransform::Identity);

	if (Egg)
	{
		AttachEgg();
	}
}

AEgg* UEggManagerComponent::GetEgg()
{
	return Egg;
}

void UEggManagerComponent::AttachEgg()
{
	if (!IsValid(Egg) || !IsValid(TargetMesh))
	{
		return;
	}

	Egg->AttachToComponent(TargetMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void UEggManagerComponent::ThrowEgg()
{
	if (!IsValid(Egg))
	{
		return;
	}
}