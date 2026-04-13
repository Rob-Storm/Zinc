#include "Soundscape.h"
#include "UObject/Object.h"

#include "Kismet/GameplayStatics.h"
#include "ZincGameMode.h"

ASoundscape::ASoundscape()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));

	RootComponent = Billboard;
}

void ASoundscape::ActivateSoundscape()
{
	AZincGameMode* GM = Cast<AZincGameMode>(UGameplayStatics::GetGameMode(this));

	if(!GM)
	{
		return;
	}

	GM->PlaySoundscape(Soundscape);
}

void ASoundscape::RegisterIOEvents(FActorIOEventList& EventRegistry)
{

}

void ASoundscape::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ASoundscape::ActivateSoundscape"))
		.SetDisplayName(INVTEXT("ActivateSoundscape"))
		.SetTooltipText(INVTEXT("Plays the soundscape specified in the actor's properties"))
		.SetFunction(TEXT("ActivateSoundscape")));
}