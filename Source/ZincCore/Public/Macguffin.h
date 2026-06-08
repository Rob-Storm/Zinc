#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ActorIOInterface.h"
#include "Interactable.h"

#include "Components/StaticMeshComponent.h"

#include "Macguffin.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollectedSignature);

UCLASS(Blueprintable, BlueprintType, PrioritizeCategories = "Macguffin")
class AMacguffin : public AActor, public IInteractable, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AMacguffin();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnCollectedSignature OnCollected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Macguffin")
	bool IsActive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Macguffin")
	TObjectPtr<USoundBase> InteractSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Macguffin")
	FText InteractionText = INVTEXT("MACGUFFIN");

	UFUNCTION(BlueprintCallable, Category="Macguffin")
	void SetActiveState(bool NewState)
	{
		IsActive = NewState;
		if(!IsActive)
		{
			Model->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
		}
		else
		{
			Model->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
		}
	}

	virtual void Interact_Implementation(AZincCharacter* CallingCharacter) override;

	virtual FText GetInteractText_Implementation() const override
	{
		return InteractionText;
	}

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
