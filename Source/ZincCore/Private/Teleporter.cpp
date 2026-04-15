#include "Teleporter.h"
#include "UObject/Object.h"

#include "Kismet/GameplayStatics.h"

ATeleporter::ATeleporter()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void ATeleporter::Teleport()
{
	if(TeleportPlayer)
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

		PlayerPawn->SetActorLocation(TargetDestination->GetActorLocation());
	}

	if(AffectedActors.Num() <= 0)
	{
		return;
	}

	for(AActor* Actor : AffectedActors)
	{
		Actor->SetActorLocation(TargetDestination->GetActorLocation());
	}
}

void ATeleporter::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ATeleporter::OnTeleported"))
		.SetDisplayName(INVTEXT("OnTeleported"))
		.SetTooltipText(INVTEXT("Event when the door is used while locked. Only triggered by players"))
		.SetMulticastDelegate(this, &OnTeleported));
}

void ATeleporter::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ATeleporter::Teleport"))
		.SetDisplayName(INVTEXT("Teleport"))
		.SetTooltipText(INVTEXT("Teleports the actor"))
		.SetFunction(TEXT("Teleport")));
}
