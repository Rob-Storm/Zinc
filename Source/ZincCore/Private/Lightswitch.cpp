#include "Lightswitch.h"
#include "UObject/Object.h"

#include "Kismet/GameplayStatics.h"

ALightswitch::ALightswitch()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
}

void ALightswitch::BeginPlay()
{
	for(ALight* Light : AffectedLights)
	{
		Light->SetEnabled(IsOn);
	}
}

void ALightswitch::Interact_Implementation(ACharacter* CallingCharacter)
{
	if(IsLocked)
	{
		return;
	}

	ToggleLight();

	if(!UseSound)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(this, UseSound, GetActorLocation());
}

void ALightswitch::ToggleLight()
{
	if(IsLocked)
	{
		return;
	}

	IsOn = !IsOn;

	for(ALight* Light : AffectedLights)
	{
		Light->SetEnabled(IsOn);
	}
}

void ALightswitch::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ALightswitch::OnUsed"))
		.SetDisplayName(INVTEXT("OnUsed"))
		.SetTooltipText(INVTEXT("Event when the light is used by the player"))
		.SetMulticastDelegate(this, &OnUsed));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ALightswitch::OnTurnedOn"))
		.SetDisplayName(INVTEXT("OnTurnedOn"))
		.SetTooltipText(INVTEXT("Event when the light is turned on"))
		.SetMulticastDelegate(this, &OnTurnedOn));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ALightswitch::OnTurnedOff"))
		.SetDisplayName(INVTEXT("OnTurnedOff"))
		.SetTooltipText(INVTEXT("Event when the light is turned off"))
		.SetMulticastDelegate(this, &OnTurnedOff));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ALightswitch::OnUnlocked"))
		.SetDisplayName(INVTEXT("OnUnlocked"))
		.SetTooltipText(INVTEXT("Event when the light is unlocked"))
		.SetMulticastDelegate(this, &OnUnlocked));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ALightswitch::OnLocked"))
		.SetDisplayName(INVTEXT("OnLocked"))
		.SetTooltipText(INVTEXT("Event when the light is locked"))
		.SetMulticastDelegate(this, &OnLocked));

}

void ALightswitch::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ALightswitch::ToggleLight"))
		.SetDisplayName(INVTEXT("ToggleLight"))
		.SetTooltipText(INVTEXT("Toggles the light on/off"))
		.SetFunction(TEXT("ToggleLight")));

	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ALightswitch::ToggleLight"))
		.SetDisplayName(INVTEXT("ToggleLight"))
		.SetTooltipText(INVTEXT("Toggles the light on/off"))
		.SetFunction(TEXT("ToggleLight")));

	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ALightswitch::SetLockState"))
		.SetDisplayName(INVTEXT("SetLockState"))
		.SetTooltipText(INVTEXT("Sets the state of the lightswitch lock"))
		.SetFunction(TEXT("SetLockState")));

}