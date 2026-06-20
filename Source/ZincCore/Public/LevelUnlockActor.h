#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "LevelUnlockActor.generated.h"

UCLASS(Blueprintable, BlueprintType, PrioritizeCategories = "Level Unlocker")
class ALevelUnlockActor : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ALevelUnlockActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	/** The name of the level you wish to unlock, refer to the DT_LevelInfo asset for names */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Unlocker")
	FString LevelName;

	UFUNCTION(BlueprintCallable, Category="Level Unlocker")
	void UnlockLevel();

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
