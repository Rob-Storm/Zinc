#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFramework/SaveGame.h"

#include "ZincSaveSlot.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UZincSaveSlot : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Main Menu", meta=(ExposeOnSpawn="true"))
	TSoftObjectPtr<UWorld> LastPlayedLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Flow", meta=(ExposeOnSpawn="true"))
	bool HasPlayedOnce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Flow", meta=(ExposeOnSpawn="true"))
	TSet<FString> UnlockedLevels;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Save Slot")
	static FString GetSaveSlotName()
	{
		return TEXT("ZincSaveSlot");
	}
	
};
