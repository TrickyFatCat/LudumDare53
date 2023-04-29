// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EggManagerComponent.generated.h"

class AEgg;
class USkeletalMeshComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UEggManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEggManagerComponent();

protected:
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

public:
	AEgg* GetEgg();

	void AttachEgg();

	void ThrowEgg();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEgg> EggClass = nullptr;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> TargetMesh = nullptr;

	UPROPERTY()
	bool bEggIsTaken = false;

	UPROPERTY(EditAnywhere)
	FName SocketName = NAME_None;

	UPROPERTY(BlueprintReadOnly)
	AEgg* Egg = nullptr;
};
