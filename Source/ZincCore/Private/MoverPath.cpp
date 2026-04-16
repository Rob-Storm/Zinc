#include "MoverPath.h"
#include "UObject/Object.h"

AMoverPath::AMoverPath()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void AMoverPath::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AMoverPath::OnMoverReached"))
		.SetDisplayName(INVTEXT("OnMoverReached"))
		.SetTooltipText(INVTEXT("Event when the mover reaches this path"))
		.SetMulticastDelegate(this, &OnMoverReached));
}

void AMoverPath::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{

}