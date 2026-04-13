#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"

#include "ActorIOInterface.h"
#include "Interactable.h"

#include "Engine/Light.h"

#include "Lightswitch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightSwitchUsedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightSwitchTurnedOnSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightSwitchTurnedOffSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightSwitchUnlockedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightSwitchLockedSignature);

UCLASS(Blueprintable, BlueprintType)
class ALightswitch : public AActor, public IInteractable, public IActorIOInterface
{
	GENERATED_BODY()

public:	

	ALightswitch();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnLightSwitchUsedSignature OnUsed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnLightSwitchTurnedOnSignature OnTurnedOn;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnLightSwitchUnlockedSignature OnTurnedOff;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnLightSwitchTurnedOnSignature OnUnlocked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnLightSwitchUnlockedSignature OnLocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UPointLightComponent> NightLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Lightswitch")
	TObjectPtr<USoundBase> UseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Lightswitch")
	TArray<ALight*> AffectedLights;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Lightswitch")
	bool IsOn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Lightswitch")
	bool IsLocked = false;

	UFUNCTION(BlueprintCallable, Category="Lightswitch")
	void ToggleLight();

	UFUNCTION(BlueprintCallable, Category="Lightswitch")
	void SetLockState(bool NewState)
	{
		IsLocked = NewState;

		if(IsLocked)
		{
			OnLocked.Broadcast();
		}
		else
		{
			OnUnlocked.Broadcast();
		}
	}

	virtual void Interact_Implementation(ACharacter* CallingCharacter) override;

	virtual FText GetInteractText_Implementation() const override
	{
		FText ReturnText = IsOn ? FText::FromString("turn off") : FText::FromString("turn on");
		return ReturnText;
	}

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};