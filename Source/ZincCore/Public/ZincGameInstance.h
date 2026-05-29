#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "ZincGameInstance.generated.h"

UCLASS()
class UZincGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float LastLookSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZincCore")
	bool ToggleCrouch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameFlow")
	bool StartCutsceneTriggered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	TMap<USoundClass*, float> SoundClassVolumes;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Volume")
	void SetClassVolume(USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Volume")
	float GetClassVolume(USoundClass* SoundClass) const
	{
		return SoundClassVolumes.FindRef(SoundClass);
	}
	
};
