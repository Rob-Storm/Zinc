#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

#include "MainMenuCamera.generated.h"

/** The location and initial rotation of the camera that will be spawned and possessed on the main menu */
UCLASS(Blueprintable, BlueprintType)
class AMainMenuCamera : public AActor
{
	GENERATED_BODY()

public:

	AMainMenuCamera();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UCameraComponent> Camera;
	
};
