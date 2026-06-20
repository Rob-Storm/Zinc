#include "LevelUnlockActor.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"

#include "ZincGameInstance.h"

ALevelUnlockActor::ALevelUnlockActor()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void ALevelUnlockActor::UnlockLevel()
{
	UZincGameInstance* GI = Cast<UZincGameInstance>(UGameplayStatics::GetGameInstance(this));

	if(!GI)
	{
		return;
	}

	GI->UnlockLevel(LevelName);
}

void ALevelUnlockActor::RegisterIOEvents(FActorIOEventList& EventRegistry)
{

}

void ALevelUnlockActor::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ALevelUnlockActor::UnlockLevel"))
		.SetDisplayName(INVTEXT("UnlockLevel"))
		.SetTooltipText(INVTEXT("Unlocks the level specified in the actor's properties"))
		.SetFunction(TEXT("UnlockLevel")));
}