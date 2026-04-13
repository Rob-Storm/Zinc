#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TimerManager.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "ActorIOInterface.h"

#include "Interactable.h"

#include "Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClosedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToggledSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnlockedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLockedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLockToggledSignature);


UCLASS()
class ADoor : public AActor, public IInteractable, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ADoor();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnOpenedSignature OnOpened;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnClosedSignature OnClosed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnToggledSignature OnToggled;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnUnlockedSignature OnUnlocked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnLockedSignature OnLocked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnLockToggledSignature OnLockToggled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USceneComponent> ModelHinge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(BlueprintReadWrite, Category="Door")
	bool IsClosed = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	bool StartOpen = false;

	UPROPERTY(BlueprintReadWrite, Category="Door")
	bool IsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	bool StartLocked = false;
	
	/** The rotation the door will use when closed. Automatically set on BeginPlay */
	UPROPERTY(BlueprintReadWrite, Category="Door")
	FRotator CloseRotation;

	/** The rotation the door will use when opened */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FRotator OpenRotation;

	/** The sound that plays upon opening the door */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	TObjectPtr<USoundBase> OpenSound;

	/** The sound that plays upon closing the door */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	TObjectPtr<USoundBase> CloseSound;

	/** The sound that plays when using the door while it is locked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	TObjectPtr<USoundBase> LockSound;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Door")
	void Open();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Door")
	void Close();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Door")
	void Toggle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Door")
	void Unlock();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Door")
	void Lock();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Door")
	void ToggleLock();

	virtual void Interact_Implementation(ACharacter* CallingCharacter) override;

	virtual FText GetInteractText_Implementation() const override
	{
		FText ReturnText = IsClosed ? FText::FromString("open door") : FText::FromString("close door");
		return ReturnText;
	}

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;

};
