#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Widgets/ErrorUI.h"
#include "ZincSaveSlot.h"

#include "ZincGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnlockedSignature, const FString&, LevelName);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameSavedSignature, UZincSaveSlot*, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoadedSignature, UZincSaveSlot*, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveGameClearedSignature);

UCLASS()
class UZincGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Game Flow")
	FOnLevelUnlockedSignature OnLevelUnlocked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Saving/Loading")
	FOnSaveGameSavedSignature OnSaveGameSaved;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Saving/Loading")
	FOnSaveGameLoadedSignature OnSaveGameLoaded;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Saving/Loading")
	FOnSaveGameClearedSignature OnSaveGameCleared;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Flow")
	bool StartCutsceneTriggered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Flow")
	bool HasPlayedOnce = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Flow")
	TSet<FString> UnlockedLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume")
	TMap<USoundClass*, float> SoundClassVolumes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Error Handling")
	TSubclassOf<UErrorUI> ErrorWidgetClass;

	/** Adds a level name to the UnlockedLevels set, does not check if level exists! */
	UFUNCTION(Exec, BlueprintNativeEvent, BlueprintCallable, Category="Game Flow")
	void UnlockLevel(const FString& LevelName);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Volume")
	void SetClassVolume(USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Volume")
	float GetClassVolume(USoundClass* SoundClass) const
	{
		return SoundClassVolumes.FindRef(SoundClass);
	}

	UFUNCTION(BlueprintCallable, Category="Error Handling")
	void ShowError(FText Caption, FText Message, bool ReturnControl);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Saving/Loading")
	void SaveData();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Saving/Loading")
	void LoadData();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Saving/Loading")
	void ClearSaveData();
	
};