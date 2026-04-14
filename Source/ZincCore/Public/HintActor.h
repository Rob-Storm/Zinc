#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "HintActor.generated.h"

UCLASS()
class AHintActor : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AHintActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UFUNCTION(BlueprintCallable, Category="Hint")
	void ShowHint(FText HintText, float Duration);

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
