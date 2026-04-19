#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

#include "ActorIOInterface.h"

#include "ElevatorStop.h"

#include "Elevator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoverStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoverEndedSignature);

UCLASS(Blueprintable, BlueprintType)
class AElevator : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AElevator();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnMoverStartedSignature OnMovingStarted;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnMoverEndedSignature OnMovingEnded;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mover")
	float Speed = 1.f;

	/** Mover actor will snap here on begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mover")
	int32 InitialStopIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mover")
	TArray<AElevatorStop*> Stops;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mover")
	TObjectPtr<USoundBase> StartSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mover")
	TObjectPtr<USoundBase> StopSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mover")
	TObjectPtr<USoundBase> LoopSound;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Mover")
	void MoveTo(int32 StopIndex);

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
