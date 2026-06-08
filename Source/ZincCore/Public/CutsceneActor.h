#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "CutsceneActor.generated.h"

/** This actor is used as a workaround for disabling the player UI since the level sequence fails for some reason */

UCLASS(Blueprintable, BlueprintType, PrioritizeCategories = "Cutscene Actor")
class ACutsceneActor : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ACutsceneActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Cutscene Actor")
	void Activate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Cutscene Actor")
	void Deactivate();

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};