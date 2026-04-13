#include "ZincGameMode.h"
#include "UObject/Object.h"

#include "SoundscapeData.h"

AZincGameMode::AZincGameMode()
{
	SoundscapePlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundscapePlayer"));
	SoundscapePlayer->SetupAttachment(RootComponent);
}

void AZincGameMode::PlaySoundscape_Implementation(class USoundscapeData* Data)
{

}