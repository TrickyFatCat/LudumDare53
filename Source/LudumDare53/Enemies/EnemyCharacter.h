// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UDeathSequenceComponent;
class UHitPointsComponent;
class UBehaviorTree;

UCLASS()
class LUDUMDARE53_API AEnemyCharacter : public ACharacter

{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	UFUNCTION()
	virtual void BeginPlay() override;

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTreeAsset; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHitPointsComponent> HitPointComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DeathSequence")
	TObjectPtr<UDeathSequenceComponent> DeathSequenceComponent;

private:
	UFUNCTION()
	void Die();

	virtual float TakeDamage(
		float DamageAmount,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;
};
