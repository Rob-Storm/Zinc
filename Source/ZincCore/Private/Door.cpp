#include "Door.h"
#include "UObject/Object.h"

#include "Kismet/GameplayStatics.h"

ADoor::ADoor()
{
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	ModelHinge = CreateDefaultSubobject<USceneComponent>(TEXT("Hinge"));
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorModel"));

	RootComponent = DoorFrame;	
	ModelHinge->SetupAttachment(RootComponent);
	Model->SetupAttachment(ModelHinge);

}

void ADoor::Open_Implementation()
{
	if(IsLocked)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LockSound, GetActorLocation());
		return;
	}

	IsClosed = false;

	ModelHinge->SetWorldRotation(OpenRotation);

	UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());


	OnOpened.Broadcast();
}

void ADoor::Close_Implementation()
{
	if(IsLocked)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LockSound, GetActorLocation());
		return;
	}

	IsClosed = true;

	ModelHinge->SetWorldRotation(CloseRotation);

	UGameplayStatics::PlaySoundAtLocation(this, CloseSound, GetActorLocation());


	OnClosed.Broadcast();
}

void ADoor::Toggle_Implementation()
{
	if(IsClosed)
	{
		Open();
	}
	else
	{
		Close();
	}

	OnToggled.Broadcast();
}

void ADoor::Unlock_Implementation()
{
	IsLocked = false;

	OnUnlocked.Broadcast();
}

void ADoor::Lock_Implementation()
{
	IsLocked = true;

	OnUnlocked.Broadcast();
}

void ADoor::ToggleLock_Implementation()
{
	IsLocked = !IsLocked;

	OnLockToggled.Broadcast();
}

void ADoor::Interact_Implementation(ACharacter* CallingCharacter)
{
	Toggle();
}

void ADoor::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ADoor::OnOpened"))
		.SetDisplayName(INVTEXT("OnOpened"))
		.SetTooltipText(INVTEXT("Event when the door is opened"))
		.SetMulticastDelegate(this, &OnOpened));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ADoor::OnClosed"))
		.SetDisplayName(INVTEXT("OnClosed"))
		.SetTooltipText(INVTEXT("Event when the door is closed"))
		.SetMulticastDelegate(this, &OnClosed));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ADoor::OnToggled"))
		.SetDisplayName(INVTEXT("OnToggled"))
		.SetTooltipText(INVTEXT("Event when the door is toggled"))
		.SetMulticastDelegate(this, &OnToggled));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ADoor::OnUnlocked"))
		.SetDisplayName(INVTEXT("OnUnlocked"))
		.SetTooltipText(INVTEXT("Event when the door is unlocked"))
		.SetMulticastDelegate(this, &OnUnlocked));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ADoor::OnLocked"))
		.SetDisplayName(INVTEXT("OnLocked"))
		.SetTooltipText(INVTEXT("Event when the door is locked"))
		.SetMulticastDelegate(this, &OnLocked));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ADoor::OnLockToggled"))
		.SetDisplayName(INVTEXT("OnLockToggled"))
		.SetTooltipText(INVTEXT("Event when the door lock state is toggled"))
		.SetMulticastDelegate(this, &OnLockToggled));
}

void ADoor::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ADoor::Open"))
		.SetDisplayName(INVTEXT("Open"))
		.SetTooltipText(INVTEXT("Opens the door"))
		.SetFunction(TEXT("Open")));

	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ADoor::Close"))
		.SetDisplayName(INVTEXT("Close"))
		.SetTooltipText(INVTEXT("Closes the door"))
		.SetFunction(TEXT("Close")));

	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ADoor::Toggle"))
		.SetDisplayName(INVTEXT("Toggle"))
		.SetTooltipText(INVTEXT("Toggles the door opened state"))
		.SetFunction(TEXT("Toggle")));

	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ADoor::Unlock"))
		.SetDisplayName(INVTEXT("Unlock"))
		.SetTooltipText(INVTEXT("Unlocks the door"))
		.SetFunction(TEXT("Unlock")));

	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ADoor::Lock"))
		.SetDisplayName(INVTEXT("Lock"))
		.SetTooltipText(INVTEXT("Locks the door"))
		.SetFunction(TEXT("Lock")));

	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ADoor::ToggleLock"))
		.SetDisplayName(INVTEXT("Toggle Lock"))
		.SetTooltipText(INVTEXT("Toggle the door lock state"))
		.SetFunction(TEXT("ToggleLock")));
}