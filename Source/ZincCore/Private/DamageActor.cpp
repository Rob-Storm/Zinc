#include "DamageActor.h"
#include "UObject/Object.h"

ADamageActor::ADamageActor()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
}

void ADamageActor::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ADamageActor::OnDamaged"))
		.SetDisplayName(INVTEXT("OnDamaged"))
		.SetTooltipText(INVTEXT("Event when this object has been damaged with damage events enabled"))
		.SetMulticastDelegate(this, &OnDamaged));
}

void ADamageActor::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{

}