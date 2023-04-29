// Made by TitledGooseTeam during Ludum Dare 53


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LudumDare53/Components/HitPointsComponent.h"
#include "LudumDare53/Components/LivesComponent.h"
#include "LudumDare53/Components/MeatCounterComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	HitPoints = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
	LivesComponent = CreateDefaultSubobject<ULivesComponent>("Lives");
	MeatCounterComponent = CreateDefaultSubobject<UMeatCounterComponent>("MeatCounter");
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	HitPoints->OnValueZero.AddDynamic(this, &APlayerCharacter::DecreaseLives);
	MeatCounterComponent->OnValueIncreased.AddDynamic(this, &APlayerCharacter::HandleMeatCounterIncrease);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::DecreaseLives()
{
	LivesComponent->DecreaseValue(1);
}

void APlayerCharacter::HandleMeatCounterIncrease(const int32 NewValue, const int32 Amount)
{
	if (HitPoints->GetValue() >= HitPoints->GetMaxValue())
	{
		return;
	}

	HitPoints->IncreaseValue(1);
}