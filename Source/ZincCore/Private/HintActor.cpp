#include "HintActor.h"
#include "UObject/Object.h"

#include "Kismet/GameplayStatics.h"

#include "ZincPlayerController.h"

AHintActor::AHintActor()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void AHintActor::ShowHint(FText HintText, float Duration)
{
	AZincPlayerController* PC = Cast<AZincPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if(!PC)
	{
		return;
	}

	PC->DisplayHint(HintText, Duration);
}

void AHintActor::RegisterIOEvents(FActorIOEventList& EventRegistry)
{

}

void AHintActor::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AHintActor::ShowHint"))
		.SetDisplayName(INVTEXT("ShowHint"))
		.SetTooltipText(INVTEXT("Shows the hint on screen for the desired duration"))
		.SetFunction(TEXT("ShowHint")));
}