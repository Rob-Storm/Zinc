#include "ButtonActor.h"
#include "UObject/Object.h"

#include "Kismet/GameplayStatics.h"

AButtonActor::AButtonActor()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
}

void AButtonActor::SetLockState(bool NewState)
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

void AButtonActor::Interact_Implementation(AZincCharacter* CallingCharacter)
{
	if(IsLocked)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LockSound, GetActorLocation());
		OnUseLocked.Broadcast();
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, UseSound, GetActorLocation());
		OnUsed.Broadcast();
	}
}

void AButtonActor::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AButtonActor::OnUsed"))
		.SetDisplayName(INVTEXT("OnUsed"))
		.SetTooltipText(INVTEXT("Event when the button is used"))
		.SetMulticastDelegate(this, &OnUsed));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AButtonActor::OnUseLocked"))
		.SetDisplayName(INVTEXT("OnUseLocked"))
		.SetTooltipText(INVTEXT("Event when the button is used while locked. Only triggered by players"))
		.SetMulticastDelegate(this, &OnUseLocked));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AButtonActor::OnUnlocked"))
		.SetDisplayName(INVTEXT("OnUnlocked"))
		.SetTooltipText(INVTEXT("Event when the button is unlocked"))
		.SetMulticastDelegate(this, &OnUnlocked));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AButtonActor::OnLocked"))
		.SetDisplayName(INVTEXT("OnLocked"))
		.SetTooltipText(INVTEXT("Event when the button is locked"))
		.SetMulticastDelegate(this, &OnLocked));
}

void AButtonActor::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AButtonActor::SetLockState"))
		.SetDisplayName(INVTEXT("SetLockState"))
		.SetTooltipText(INVTEXT("Sets the lock state of the button"))
		.SetFunction(TEXT("SetLockState")));
}