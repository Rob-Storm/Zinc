#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

#include "ActorIOInterface.h"

#include "MoverPath.h"

#include "Mover.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoverStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoverPausedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoverEndedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPathReachedSignature);

UCLASS(Blueprintable, BlueprintType)
class AMover : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AMover();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnMoverStartedSignature OnMovingStarted;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnMoverPausedSignature OnMoverPaused;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnMoverEndedSignature OnMovingEnded;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnPathReachedSignature OnPathReached;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	/** Mover actor will snap here on begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mover")
	TObjectPtr<AMoverPath> InitialPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mover")
	TObjectPtr<AMoverPath> TargetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZincCore")
	TObjectPtr<USoundBase> StartSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZincCore")
	TObjectPtr<USoundBase> EndSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZincCore")
	TObjectPtr<USoundBase> LoopSound;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Mover")
	void StartMove();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Mover")
	void StopMove();

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
