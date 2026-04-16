#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "LevelLoad.generated.h"

UCLASS()
class ALevelLoad : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ALevelLoad();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelLoad")
	TSoftObjectPtr<UWorld> LevelToLoad;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="LevelLoad")
	void Load();

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
