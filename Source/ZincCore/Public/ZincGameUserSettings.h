#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"

#include "ZincGameUserSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFOVChangedSignature, float, NewFOV);

UCLASS()
class UZincGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Delegates")
	FOnFOVChangedSignature OnFOVChanged;

	UFUNCTION(BlueprintCallable, Category="Settings")
	static UZincGameUserSettings* GetZincUserSettings()
	{
		return Cast<UZincGameUserSettings>(UGameUserSettings::GetGameUserSettings());
	}

	UPROPERTY(config, BlueprintReadOnly)
	float LookSensitivity = 1.f;

	UPROPERTY(config, BlueprintReadOnly)
	bool ToggleCrouch = false;

	UPROPERTY(config, BlueprintReadOnly)
	float CameraFOV = 90.f;

	UFUNCTION(BlueprintCallable)
	void SetLookSensitivity(float NewValue)
	{
		LookSensitivity = NewValue;

		SaveSettings();
	}

	UFUNCTION(BlueprintCallable)
	void SetToggleCrouch(bool NewValue)
	{
		ToggleCrouch = NewValue;

		SaveSettings();
	}

	UFUNCTION(BlueprintCallable)
	void SetCameraFOV(float NewValue)
	{
		CameraFOV = NewValue;

		OnFOVChanged.Broadcast(NewValue);

		SaveSettings();
	}
	
};
