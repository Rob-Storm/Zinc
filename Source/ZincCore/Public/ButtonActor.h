#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "ActorIOInterface.h"

#include "Interactable.h"

#include "ButtonActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUsedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonUseLockedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonUnlockedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonLockedSignature);

UCLASS(PrioritizeCategories = "Button")
class AButtonActor : public AActor, public IInteractable, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AButtonActor();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnUsedSignature OnUsed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnButtonUseLockedSignature OnUseLocked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnButtonUnlockedSignature OnUnlocked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnButtonLockedSignature OnLocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button")
	FText InteractTextOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button")
	bool IsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button")
	TObjectPtr<USoundBase> UseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button")
	TObjectPtr<USoundBase> LockSound;

	UFUNCTION(BlueprintCallable, Category="Button")
	void SetLockState(bool NewState);

	virtual void Interact_Implementation(AZincCharacter* CallingCharacter) override;

	virtual FText GetInteractText_Implementation() const override
	{
		if(InteractTextOverride.IsEmptyOrWhitespace())
		{
			return FText::FromString("use button");
		}
		else
		{
			return InteractTextOverride;
		}
	}

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
