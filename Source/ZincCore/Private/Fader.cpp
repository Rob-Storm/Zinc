#include "Fader.h"
#include "UObject/Object.h"

AFader::AFader()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void AFader::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AFader::OnFadeStarted"))
		.SetDisplayName(INVTEXT("OnFadeStarted"))
		.SetTooltipText(INVTEXT("Event when fade begins"))
		.SetMulticastDelegate(this, &OnFadeStarted));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AFader::OnFadeFinished"))
		.SetDisplayName(INVTEXT("OnFadeFinished"))
		.SetTooltipText(INVTEXT("Event when the fade ends"))
		.SetMulticastDelegate(this, &OnFadeFinished));
}

void AFader::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AFader::Fade"))
		.SetDisplayName(INVTEXT("Fade"))
		.SetTooltipText(INVTEXT("Fades screen to color"))
		.SetFunction(TEXT("Fade")));
}