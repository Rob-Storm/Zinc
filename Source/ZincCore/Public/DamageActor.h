#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "Damageable.h"
#include "ActorIOInterface.h"

#include "DamageActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamagedSignature);

UCLASS(Blueprintable, BlueprintType)
class ADamageActor : public AActor, public IDamageable, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ADamageActor();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Damage Actor")
	FOnDamagedSignature OnDamaged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	virtual void Damage_Implementation(int32 DamageAmount, EDamageType DamageType, class AZincCharacter* Attacker) override
	{
		OnDamaged.Broadcast();
	}

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
