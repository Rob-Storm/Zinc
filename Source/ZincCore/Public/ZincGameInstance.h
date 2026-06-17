#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Widgets/ErrorUI.h"

#include "ZincGameInstance.generated.h"

UCLASS()
class UZincGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameFlow")
	bool StartCutsceneTriggered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	TMap<USoundClass*, float> SoundClassVolumes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Error Handling")
	TSubclassOf<UErrorUI> ErrorWidgetClass;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Volume")
	void SetClassVolume(USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Volume")
	float GetClassVolume(USoundClass* SoundClass) const
	{
		return SoundClassVolumes.FindRef(SoundClass);
	}

	UFUNCTION(BlueprintCallable, Category="Error Handling")
	void ShowError(FText Caption, FText Message, bool ReturnControl);
	
};
