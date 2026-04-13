#include "ZincPlayer.h"
#include "UObject/Object.h"

#include "Kismet/GameplayStatics.h"

#include "Interactable.h"
#include "ZincPlayerController.h"

#include "Kismet/GameplayStatics.h"

AZincPlayer::AZincPlayer()
{
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	FirstPersonCamera->SetupAttachment(RootComponent);

}

AActor* AZincPlayer::InteractTrace(float Range)
{
	FVector StartLocation;
	FVector EndLocation;
	FHitResult Result;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FCollisionResponseParams ResponseParams;

	StartLocation = FirstPersonCamera->GetComponentLocation();
	EndLocation = StartLocation + (FirstPersonCamera->GetForwardVector() * Range);

	GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams, ResponseParams);

	return Result.GetActor();

}

void AZincPlayer::TryGetInteractionText_Implementation(float Range)
{
	AActor* InteractActor = InteractTrace(Range);

	AZincPlayerController* PC = Cast<AZincPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if(!PC)
	{
		return;
	}

	if(!InteractActor)
	{
		PC->HideInteractText();
		return;
	}

	if(InteractActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		FText InteractText = IInteractable::Execute_GetInteractText(InteractActor);
		PC->DisplayInteractText(InteractText);
	}
}