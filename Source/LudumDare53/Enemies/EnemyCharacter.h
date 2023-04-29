// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UBehaviorTree;
class ULivesComponent;

UCLASS()
class LUDUMDARE53_API AEnemyCharacter : public ACharacter

{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Character")
	void OnDeathFinished();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<ULivesComponent> LivesComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animations")
	TObjectPtr<UAnimMontage> DeathMontage = nullptr;

	UFUNCTION()
	void PlayDeathMontage(AController* DeathInstigator, AActor* DeathCauser, const UDamageType* DamageType);
};
