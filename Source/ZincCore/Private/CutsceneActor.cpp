#include "CutsceneActor.h"
#include "UObject/Object.h"

ACutsceneActor::ACutsceneActor()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void ACutsceneActor::RegisterIOEvents(FActorIOEventList& EventRegistry)
{

}

void ACutsceneActor::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ACutsceneActor::Activate"))
		.SetDisplayName(INVTEXT("Activate"))
		.SetTooltipText(INVTEXT("Activates cutscene mode on the player controller and removes the UI"))
		.SetFunction(TEXT("Activate")));
}