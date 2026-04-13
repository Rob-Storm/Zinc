#include "Trigger.h"
#include "UObject/Object.h"

#include "ZincPlayer.h"

ATrigger::ATrigger()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;

	TriggerBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBounds"));
	TriggerBounds->SetupAttachment(RootComponent);

	AffectedActorClasses.Add(AZincPlayer::StaticClass());
}

void ATrigger::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ATrigger::OnTriggerEnter"))
		.SetDisplayName(INVTEXT("OnTriggerEnter"))
		.SetTooltipText(INVTEXT("Event when an AffectedActor enters the trigger"))
		.SetMulticastDelegate(this, &OnTriggerEnter));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ATrigger::OnTriggerExit"))
		.SetDisplayName(INVTEXT("OnTriggerExit"))
		.SetTooltipText(INVTEXT("Event when an AffectedActor exits the trigger"))
		.SetMulticastDelegate(this, &OnTriggerExit));
}

void ATrigger::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ATrigger::SetActive"))
		.SetDisplayName(INVTEXT("SetActive"))
		.SetTooltipText(INVTEXT("Sets the active state of the trigger"))
		.SetFunction(TEXT("SetActive")));
}