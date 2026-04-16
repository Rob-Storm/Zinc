#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "ElevatorStop.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoverReachedSignature);

UCLASS(Blueprintable, BlueprintType)
class AElevatorStop : public AActor
{
	GENERATED_BODY()

public:

	AElevatorStop();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnMoverReachedSignature OnMoverReached;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;
};
