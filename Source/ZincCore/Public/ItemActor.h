#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "ActorIOInterface.h"
#include "Interactable.h"

#include "ItemData.h"

#include "ItemActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemPickedUpSignature);

UCLASS()
class AItemActor : public AActor, public IInteractable, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AItemActor();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Delegates")
	FOnItemPickedUpSignature OnItemPickedUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool CanPickUp = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TObjectPtr<UItemData> ItemData;

	UFUNCTION(BlueprintCallable, Category="Item")
	void SetCanPickUpState(bool NewState)
	{
		CanPickUp = NewState;
	}

	UFUNCTION(BlueprintCallable, Category="ZincCore")
	void SetItemData(UItemData* NewData)
	{
		ItemData = NewData;

		Model->SetStaticMesh(ItemData->WorldModel);
	}

	virtual void Interact_Implementation(AZincCharacter* CallingCharacter) override;

	virtual FText GetInteractText_Implementation() const override
	{
		FString ReturnText = TEXT("pick up ") + ItemData->ItemName.ToString();
		return FText::FromString(ReturnText);
	}

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif
};
