#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "MoverPath.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoverReachedSignature);

UCLASS(Blueprintable, BlueprintType)
class AMoverPath : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AMoverPath();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnMoverReachedSignature OnMoverReached;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoverPath")
	TObjectPtr<AMoverPath> NextPath;

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
