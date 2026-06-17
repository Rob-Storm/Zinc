#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ErrorUI.generated.h"

UCLASS()
class UErrorUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Error UI", meta=(ExposeOnSpawn="true"))
	FText CaptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Error UI", meta=(ExposeOnSpawn="true"))
	FText MessageText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Error UI", meta=(ExposeOnSpawn="true"))
	bool ReturnControl;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Error UI")
	void PopulateUI();
	
};
