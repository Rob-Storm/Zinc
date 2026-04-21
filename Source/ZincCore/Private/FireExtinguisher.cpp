#include "FireExtinguisher.h"
#include "UObject/Object.h"

AFireExtinguisher::AFireExtinguisher()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
}