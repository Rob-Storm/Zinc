#include "LevelLoad.h"
#include "UObject/Object.h"

ALevelLoad::ALevelLoad()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void ALevelLoad::RegisterIOEvents(FActorIOEventList& EventRegistry)
{

}

void ALevelLoad::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ALevelLoad::Load"))
		.SetDisplayName(INVTEXT("Load"))
		.SetTooltipText(INVTEXT("Loads the level set in the actor's properties"))
		.SetFunction(TEXT("Load")));
}
