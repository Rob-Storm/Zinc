#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Widgets/ErrorUI.h"

#include "ZincGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnlockedSignature, const FString&, LevelName);

UCLASS()
class UZincGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Game Flow")
	FOnLevelUnlockedSignature OnLevelUnlocked;

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
	UFUNCTION(Exec, BlueprintCallable, Category="Game Flow")
	void UnlockLevel(const FString& LevelName)
	{
		UE_LOG(LogTemp, Log, TEXT("Unlocked level '%s'"), *LevelName);
		UnlockedLevels.Add(LevelName);

		OnLevelUnlocked.Broadcast(LevelName);
	}

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
