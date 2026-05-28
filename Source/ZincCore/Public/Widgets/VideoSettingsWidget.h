#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "VideoSettingsWidget.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UVideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:

	UFUNCTION(BlueprintCallable, Category="Settings")
	void SetQualityPreset(int Level = 0);
	
};
