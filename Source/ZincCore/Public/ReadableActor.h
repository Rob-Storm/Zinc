#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "Interactable.h"
#include "ReadableData.h"

#include "ActorIOInterface.h"

#include "ReadableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReadSignature);

UCLASS(Blueprintable, BlueprintType, PrioritizeCategories = "Readable")
class AReadableActor : public AActor, public IInteractable, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AReadableActor();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Readable")
	FOnReadSignature OnRead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Readable")
	TObjectPtr<UReadableData> ReadableData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Readable")
	TObjectPtr<USoundBase> InteractSound;
	
	virtual void Interact_Implementation(AZincCharacter* CallingCharacter) override;

	virtual FText GetInteractText_Implementation() const override
	{
		FString ReturnText = TEXT("read document (") + ReadableData->Title.ToString() + TEXT(")");
		return FText::FromString(ReturnText);
	}

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

};
