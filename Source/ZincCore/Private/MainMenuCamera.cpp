#include "MainMenuCamera.h"
#include "UObject/Object.h"

AMainMenuCamera::AMainMenuCamera()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
}