// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "AbilityComponent.h"
#include "GoblinEggAbilityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UGoblinEggAbilityComponent : public UAbilityComponent
{
	GENERATED_BODY()

public:
	virtual bool ActivateAbility() override;
	virtual bool DeactivateAbility() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	float SpeedWithEgg = 150.0;

private:
	float PreviousSpeed;
};
