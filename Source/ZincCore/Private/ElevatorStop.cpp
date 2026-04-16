#include "ElevatorStop.h"
#include "UObject/Object.h"

AElevatorStop::AElevatorStop()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}