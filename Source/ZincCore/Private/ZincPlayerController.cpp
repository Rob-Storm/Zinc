#include "ZincPlayerController.h"
#include "ZincGameInstance.h"

#include "Kismet/GameplayStatics.h"

void AZincPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AZincPlayerController::SetLookSensitivity(float NewSensitivity)
{
	LookSensitivity = NewSensitivity;
}