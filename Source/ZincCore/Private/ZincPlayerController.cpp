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

	TObjectPtr<UZincGameInstance> GI = Cast<UZincGameInstance>(UGameplayStatics::GetGameInstance(this));

	if(GI)
	{
		GI->LastLookSensitivity = NewSensitivity;
	}

}