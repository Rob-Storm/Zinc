#include "Elevator.h"
#include "UObject/Object.h"

AElevator::AElevator()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AElevator::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AElevator::OnMovingStarted"))
		.SetDisplayName(INVTEXT("OnMovingStarted"))
		.SetTooltipText(INVTEXT("Event when the object begins moving"))
		.SetMulticastDelegate(this, &OnMovingStarted));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AElevator::OnMovingEnded"))
		.SetDisplayName(INVTEXT("OnMovingEnded"))
		.SetTooltipText(INVTEXT("Event when the object has reached a path with no next path"))
		.SetMulticastDelegate(this, &OnMovingEnded));
}

void AElevator::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AElevator::MoveTo"))
		.SetDisplayName(INVTEXT("MoveTo"))
		.SetTooltipText(INVTEXT("Moves elevator to stop"))
		.SetFunction(TEXT("MoveTo")));
}