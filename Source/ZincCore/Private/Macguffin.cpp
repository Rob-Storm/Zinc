#include "Macguffin.h"
#include "UObject/Object.h"

#include "Kismet/GameplayStatics.h"

AMacguffin::AMacguffin()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
}

void AMacguffin::Interact_Implementation(ACharacter* CallingCharacter)
{
	OnCollected.Broadcast();
	UGameplayStatics::PlaySoundAtLocation(this, InteractSound, GetActorLocation());
	Destroy();
}

void AMacguffin::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AMacguffin::OnCollected"))
		.SetDisplayName(INVTEXT("OnCollected"))
		.SetTooltipText(INVTEXT("Event when this object is interacted with"))
		.SetMulticastDelegate(this, &OnCollected));
}

void AMacguffin::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{

}