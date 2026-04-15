#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "TeleportDestination.h"

#include "Teleporter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTeleportedSignature);

UCLASS(Blueprintable, BlueprintType)
class ATeleporter : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ATeleporter();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnTeleportedSignature OnTeleported;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Teleporter")
	bool TeleportPlayer = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Teleporter")
	TArray<AActor*> AffectedActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Teleporter")
	TObjectPtr<ATeleportDestination> TargetDestination;

	UFUNCTION(BlueprintCallable, Category="Teleporter")
	void Teleport();

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
};
