// Made by TitledGooseTeam during Ludum Dare 53

#pragma once

#include "CoreMinimal.h"
#include "Components/SimpleResourceComponent.h"
#include "MeatCounterComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE53_API UMeatCounterComponent : public USimpleResourceComponent
{
	GENERATED_BODY()

public:
	UMeatCounterComponent();
};
