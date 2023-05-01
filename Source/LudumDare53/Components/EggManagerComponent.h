// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EggManagerComponent.generated.h"

class AEgg;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEggSetSignature, AEgg*, Egg);

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
	UPROPERTY(BlueprintAssignable)
	FOnEggSetSignature OnEggSet;
	
	UFUNCTION()
	void ThrowEgg(const FVector& Direction, const float Power);

	void SetEgg(AEgg* NewEgg);

	AEgg* GetEgg() const { return Egg; }
	
	bool bIsEggInHands = false;
	
protected:
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> TargetMesh = nullptr;

	UPROPERTY(EditAnywhere)
	FName SocketName = NAME_None;

	UPROPERTY(BlueprintReadOnly)
	AEgg* Egg = nullptr;
};
