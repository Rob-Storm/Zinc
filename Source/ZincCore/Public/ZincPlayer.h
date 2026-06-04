#pragma once

#include "CoreMinimal.h"
#include "ZincCharacter.h"

#include "Camera/CameraComponent.h"

#include "ZincPlayer.generated.h"

UCLASS()
class AZincPlayer : public AZincCharacter
{
	GENERATED_BODY()

public:

	AZincPlayer();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Interaction")
	AActor* InteractTrace(float Range, bool DebugTrace);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void TryGetInteractionText(float Range, bool DebugTrace);

	UFUNCTION()
	void HandleFOVChanged(float NewFOV);
	
};
