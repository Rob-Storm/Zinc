#include "ZincPlayerController.h"

void AZincPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AZincPlayerController::SetLookSensitivity(float NewSensitivity)
{
	LookSensitivity = NewSensitivity;
}