// Made by TitledGooseTeam during Ludum Dare 53


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LudumDare53/Components/HitPointsComponent.h"
#include "LudumDare53/Components/LivesComponent.h"
#include "LudumDare53/Components/MeatCounterComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameModeSession.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractionQueueComponent.h"
#include "PlayerControllerSession.h"
#include "TrickyGameModeLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LudumDare53/Egg.h"
#include "LudumDare53/Components/EggManagerComponent.h"
#include "LudumDare53/Components/PlayerDeathSequenceComponent.h"
#include "LudumDare53/Components/StarsCounterComponent.h"
#include "LudumDare53/Components/StunComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	HitPoints = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
	LivesComponent = CreateDefaultSubobject<ULivesComponent>("Lives");
	MeatCounter = CreateDefaultSubobject<UMeatCounterComponent>("MeatCounter");
	DeathSequence = CreateDefaultSubobject<UPlayerDeathSequenceComponent>("DeathSequence");
	InteractionQueue = CreateDefaultSubobject<UInteractionQueueComponent>("InteractionQueue");
	EggManager = CreateDefaultSubobject<UEggManagerComponent>("EggManager");
	StarsCounter = CreateDefaultSubobject<UStarsCounterComponent>("StarsCounter");
	StunComponent = CreateDefaultSubobject<UStunComponent>("StunComponent");
	InvulnerabilityComponent = CreateDefaultSubobject<UStunComponent>("InvulnerabilityComponent");

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 256.f, 0.f);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	HitPoints->OnValueZero.AddDynamic(this, &APlayerCharacter::DecreaseLives);
	MeatCounter->OnValueIncreased.AddDynamic(this, &APlayerCharacter::HandleMeatCounterIncrease);
	LivesComponent->OnValueDecreased.AddDynamic(this, &APlayerCharacter::HandleLivesDecrease);
	DeathSequence->OnRespawnFinished.AddDynamic(this, &APlayerCharacter::HandleRespawn);
	DefaultGravityScale = GetCharacterMovement()->GravityScale;
	StunComponent->OnStunStarted.AddDynamic(this, &APlayerCharacter::HandleStunStarted);
	StunComponent->OnStunFinished.AddDynamic(this, &APlayerCharacter::HandleStunFinished);

	AEgg* Egg = EggManager->GetEgg();

	if (Egg)
	{
		UHitPointsComponent* HitPointsComponent = Egg->FindComponentByClass<UHitPointsComponent>();

		if (HitPointsComponent)
		{
			HitPointsComponent->OnValueZero.AddDynamic(this, &APlayerCharacter::HandleEggDeath);
		}
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void APlayerCharacter::ToggleHat(const bool bIsVisible)
{
	bHasHat = bIsVisible;
	OnHatChanged(bHasHat);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->GravityScale = DefaultGravityScale + GravityScaleDelta * (GetCharacterMovement()->
			Velocity.Z < 0.0);
	}
	else
	{
		GetCharacterMovement()->GravityScale = DefaultGravityScale;
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction,
		                                   ETriggerEvent::Triggered,
		                                   this,
		                                   &APlayerCharacter::StartInteraction);

		//ThrowEgg
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Throw);

		//Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::HandlePause);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::DecreaseLives()
{
	LivesComponent->DecreaseValue(1);
}

void APlayerCharacter::HandleMeatCounterIncrease(const int32 NewValue, const int32 Amount)
{
	if (NewValue >= MeatCounter->GetMaxValue())
	{
		LivesComponent->IncreaseValue(1);
	}
	if (HitPoints->GetValue() < HitPoints->GetMaxValue())
	{
		HitPoints->IncreaseValue(1);
	}
}

void APlayerCharacter::HandleLivesDecrease(const int32 NewValue, const int32 Amount)
{
	StunComponent->StopStun();
	DeathSequence->SetIsGameOver(LivesComponent->GetValue() == 0);
	DeathSequence->StartDeathSequence(bIsEggDestroyed);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ToggleInput(false);
}

void APlayerCharacter::HandleEggDeath()
{
	bIsEggDestroyed = true;
	LivesComponent->DecreaseValue(1);
}

void APlayerCharacter::HandleRespawn()
{
	if (DeathSequence->GetIsGameOver())
	{
		UTrickyGameModeLibrary::GetSessionGameMode(GetWorld())->FinishSession(false);
		return;
	}

	const FName LevelName = *UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void APlayerCharacter::HandleStunStarted()
{
	ToggleInput(false);
}

void APlayerCharacter::HandleStunFinished()
{
	if (HitPoints->GetValue() <= 0)
	{
		return;
	}
	
	ToggleInput(true);
}

void APlayerCharacter::HandlePause()
{
	APlayerControllerSession* SessionController = Cast<APlayerControllerSession>(GetController());

	if (SessionController)
	{
		SessionController->PauseGame();
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount,
                                   FDamageEvent const& DamageEvent,
                                   AController* EventInstigator,
                                   AActor* DamageCauser)
{
	FVector Direction = GetActorLocation();
 
 	if (DamageCauser)
 	{
 		Direction = Direction - DamageCauser->GetActorLocation();
 		Direction = Direction.GetUnsafeNormal();
 		Direction.Z = 1.0;
 	}
 	else
 	{
 		Direction = FVector::UpVector  + GetActorForwardVector() * -1;
 	}

	FVector EggDirection = Direction;
	EggDirection.X *= -1;
	EggDirection.Y *= -1;
	EggDirection = EggDirection.RotateAngleAxis(45, GetActorRightVector());
	EggManager->ThrowEgg(EggDirection, StunComponent->ThrowPower);
	
	if (InvulnerabilityComponent->GetIsStunned())
	{
		return 0.f;
	}
	
	LaunchCharacter(Direction * StunComponent->StunPower, true, true);
	HitPoints->DecreaseValue(DamageAmount);
	
	StunComponent->ApplyStun();
	InvulnerabilityComponent->ApplyStun();
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void APlayerCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	InvulnerabilityComponent->StopStun();
	HitPoints->DecreaseValue(HitPoints->GetValue());
}

void APlayerCharacter::ToggleInput(const bool bIsEnabled)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (!PlayerController)
	{
		return;
	}

	bIsEnabled ? EnableInput(PlayerController) : DisableInput(PlayerController);
}

void APlayerCharacter::StartInteraction()
{
	InteractionQueue->StartInteraction();
}

void APlayerCharacter::Throw()
{
	FVector Direction = GetActorUpVector();
	Direction = Direction.RotateAngleAxis(45, GetActorRightVector());
	EggManager->ThrowEgg(Direction, ThrowPower);

}

void APlayerCharacter::Jump()
{
	Super::Jump();
	OnJumpStarted.Broadcast();
}
