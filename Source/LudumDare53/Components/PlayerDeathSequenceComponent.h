// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "DeathSequenceComponent.h"
#include "PlayerDeathSequenceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UPlayerDeathSequenceComponent : public UDeathSequenceComponent
{
	GENERATED_BODY()

public:
	UPlayerDeathSequenceComponent();

protected:
	virtual void InitializeComponent() override;

	virtual void HandleDeathSequenceFinish() override;

};
