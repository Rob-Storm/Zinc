#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HintTextUI.generated.h"

UCLASS()
class UHintTextUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Activate(const FText& HintText = INVTEXT("Hello"), int32 Duration = 5);
	
};
