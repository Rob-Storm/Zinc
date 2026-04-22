#include "MacguffinSpawner.h"
#include "UObject/Object.h"

AMacguffinSpawner::AMacguffinSpawner()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void AMacguffinSpawner::BeginPlay()
{
	Super::BeginPlay();

	if(SpawnOnBeginPlay)
	{
		Spawn();
	}
}

void AMacguffinSpawner::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AMacguffinSpawner::OnSpawned"))
		.SetDisplayName(INVTEXT("OnSpawned"))
		.SetTooltipText(INVTEXT("Event when the macguffin has been spawned"))
		.SetMulticastDelegate(this, &OnSpawned));
}

void AMacguffinSpawner::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AMacguffinSpawner::Spawn"))
		.SetDisplayName(INVTEXT("Spawn"))
		.SetTooltipText(INVTEXT("'Spawns' your macguffin actor"))
		.SetFunction(TEXT("Spawn")));
}