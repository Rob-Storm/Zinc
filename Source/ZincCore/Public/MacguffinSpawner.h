#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "Engine/TargetPoint.h"
#include "Macguffin.h"

#include "MacguffinSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnedSignature);

/** Technically does not create objects as much as it moves an existing one */

UCLASS(Blueprintable, BlueprintType, PrioritizeCategories = "Macguffin Spawner")
class AMacguffinSpawner : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AMacguffinSpawner();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnSpawnedSignature OnSpawned;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Macguffin Spawner")
	bool SpawnOnBeginPlay = true;

	/** Remember, the actor has to exist in the world */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Macguffin Spawner")
	TObjectPtr<AActor> TargetMacguffin;

	/** Locations to move the target macguffin to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Macguffin Spawner")
	TArray<ATargetPoint*> Locations;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Macguffin Spawner")
	void Spawn();

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
