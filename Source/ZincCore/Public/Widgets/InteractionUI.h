#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InteractionUI.generated.h"

UCLASS()
class UInteractionUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateText(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HideText();
	
};
