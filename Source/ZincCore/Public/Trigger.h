#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"

#include "ActorIOInterface.h"

#include "Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerEnterSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerExitSignature);

UCLASS()
class ATrigger : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ATrigger();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Trigger")
	FOnTriggerEnterSignature OnTriggerEnter;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Trigger")
	FOnTriggerExitSignature OnTriggerExit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBoxComponent> TriggerBounds;

	/** Classes that can activate the trigger's OnEnter and OnExit functions */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	TArray<TSubclassOf<AActor>> AffectedActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	bool IsActive = true;

	UFUNCTION(BlueprintCallable, Category="Trigger")
	void SetActive(bool ActiveState)
	{
		IsActive = ActiveState;
	}

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
};
