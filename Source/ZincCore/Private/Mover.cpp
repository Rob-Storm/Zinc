#include "Mover.h"
#include "UObject/Object.h"

AMover::AMover()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AMover::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AMover::OnMovingStarted"))
		.SetDisplayName(INVTEXT("OnMovingStarted"))
		.SetTooltipText(INVTEXT("Event when the object begins moving"))
		.SetMulticastDelegate(this, &OnMovingStarted));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AMover::OnMovingEnded"))
		.SetDisplayName(INVTEXT("OnMovingEnded"))
		.SetTooltipText(INVTEXT("Event when the object has stopped moving"))
		.SetMulticastDelegate(this, &OnMovingEnded));	
}

void AMover::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AMover::StartMove"))
		.SetDisplayName(INVTEXT("StartMove"))
		.SetTooltipText(INVTEXT("Starts moving this object"))
		.SetFunction(TEXT("StartMove")));

	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AMover::StopMove"))
		.SetDisplayName(INVTEXT("StopMove"))
		.SetTooltipText(INVTEXT("Stops moving this object"))
		.SetFunction(TEXT("StopMove")));
}