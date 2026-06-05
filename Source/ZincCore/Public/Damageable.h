#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Damageable.generated.h"

UENUM(BlueprintType)
enum EDamageType
{
	Gun,
	Melee,
	Stun,
	Fall,
	Custom
};

UINTERFACE()
class ZINCCORE_API UDamageable : public UInterface
{
	GENERATED_BODY()
};

class ZINCCORE_API IDamageable
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Damageable")
	void Damage(int32 DamageAmount, EDamageType DamageType, class AZincCharacter* Attacker);

	virtual void Damage_Implementation(int32 DamageAmount, EDamageType DamageType, class AZincCharacter* Attacker);
};
