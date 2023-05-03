// Made by TitledGooseTeam during Ludum Dare 53


#include "Egg.h"

#include "SphereInteractionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/EggHitPointsComponent.h"
#include "Components/EggManagerComponent.h"
#include "Components/StunComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"


AEgg::AEgg()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	SetRootComponent(CapsuleComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	MovementComponent->bComponentShouldUpdatePhysicsVolume = true;

	HitPoints = CreateDefaultSubobject<UEggHitPointsComponent>("HitPoints");
	StunComponent = CreateDefaultSubobject<UStunComponent>("StunComponent");
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	InteractionTrigger = CreateDefaultSubobject<USphereInteractionComponent>("InteractionTrigger");
	InteractionTrigger->SetupAttachment(GetRootComponent());
	InteractionTrigger->SetInteractionMessage(this, "Pickup");
}

void AEgg::BeginPlay()
{
	Super::BeginPlay();

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerCharacter)
	{
		UEggManagerComponent* EggManager = PlayerCharacter->FindComponentByClass<UEggManagerComponent>();

		if (EggManager)
		{
			EggManager->SetEgg(this);
		}
	}

	MovementComponent->OnProjectileBounce.AddDynamic(this, &AEgg::HandleLanding);
	MovementComponent->OnProjectileStop.AddDynamic(this, &AEgg::HandleFinishSimulation);
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

	Attach(OtherActor);
	EggManager->bIsEggInHands = true;
	OnEggTaken.Broadcast();
	return true;
}

void AEgg::ToggleCollision(const bool bIsEnabled) const
{
	const ECollisionEnabled::Type CollisionEnabled = bIsEnabled
		                                                 ? ECollisionEnabled::QueryAndPhysics
		                                                 : ECollisionEnabled::NoCollision;
	MovementComponent->bSimulationEnabled = bIsEnabled;
	CapsuleComponent->SetCollisionEnabled(CollisionEnabled);
	Mesh->SetCollisionEnabled(CollisionEnabled);

	if (!bIsEnabled)
	{
		InteractionTrigger->SetCollisionEnabled(CollisionEnabled);
		CapsuleComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel14, ECR_Ignore);
	}
}

void AEgg::Attach(const AActor* OtherActor)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	USkeletalMeshComponent* TargetMesh = OtherActor->FindComponentByClass<USkeletalMeshComponent>();

	if (!TargetMesh)
	{
		return;
	}

	bIsAttached = true;
	ToggleCollision(false);
	const FHitResult HitResult;
	MovementComponent->StopSimulating(HitResult);
	AttachToComponent(TargetMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void AEgg::HandleLanding(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	InteractionTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel14, ECollisionResponse::ECR_Block);
}

void AEgg::HandleFinishSimulation(const FHitResult& HitResult)
{
	if (bIsAttached)
	{
		return; 
	}
	
	MovementComponent->SetUpdatedComponent(GetRootComponent());
}


void AEgg::Throw(const FVector& Direction, const float Power)
{
	bIsAttached = false;
	MovementComponent->InitialSpeed = Power;
	ToggleCollision(true);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	MovementComponent->Velocity = Direction * Power;
	MovementComponent->SetUpdatedComponent(GetRootComponent());
}

float AEgg::TakeDamage(float DamageAmount,
                       FDamageEvent const& DamageEvent,
                       AController* EventInstigator,
                       AActor* DamageCauser)
{
	if (StunComponent->GetIsStunned())
	{
		return 0.f;
	}


	FVector Direction = GetActorLocation();

	if (DamageCauser)
	{
		Direction = Direction - DamageCauser->GetActorLocation();
		Direction = Direction.GetUnsafeNormal();
		Direction.Z = 1.0;
	}
	else
	{
		Direction = FVector::UpVector + GetActorForwardVector() * -1;
	}

	Throw(Direction, StunComponent->ThrowPower);
	StunComponent->ApplyStun();
	HitPoints->DecreaseValue(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEgg::FellOutOfWorld(const UDamageType& dmgType)
{
	HitPoints->DecreaseValue(HitPoints->GetValue());
}
