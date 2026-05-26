#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "ZincPlayerController.generated.h"

UCLASS()
class AZincPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float LookSensitivity = 1.0f;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Hint")
	void DisplayHint(const FText& HintText = INVTEXT("Hint"), int32 Duration = 5);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Interaction")
	void DisplayInteractText(const FText& HintText = INVTEXT("InteractableText"));

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Interaction")
	void HideInteractText();

	UFUNCTION(Exec, BlueprintCallable, Category="Input")
	void SetLookSensitivity(float NewSensitivity);

	virtual void BeginPlay() override;
	
};
