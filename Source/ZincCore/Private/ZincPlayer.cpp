#include "ZincPlayer.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Interactable.h"
#include "ZincPlayerController.h"

AZincPlayer::AZincPlayer()
{
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh());

	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	MovementComponent->SetCrouchedHalfHeight(20.f);

}

AActor* AZincPlayer::InteractTrace(float Range, bool DebugTrace)
{
	FVector StartLocation;
	FVector EndLocation;
	FHitResult Result;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FCollisionResponseParams ResponseParams;

	if(DebugTrace)
	{
		FName TraceTag("InteractTraceTag");
		GetWorld()->DebugDrawTraceTag = TraceTag;

		QueryParams.TraceTag = TraceTag;
	}

	StartLocation = FirstPersonCamera->GetComponentLocation();
	EndLocation = StartLocation + (FirstPersonCamera->GetForwardVector() * Range);

	GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams, ResponseParams);

	return Result.GetActor();
}

void AZincPlayer::TryGetInteractionText_Implementation(float Range, bool DebugTrace)
{
	AActor* InteractActor = InteractTrace(Range, DebugTrace);

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