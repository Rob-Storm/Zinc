#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "ZincMainMenuGameMode.h"

#include "ZincGameplayStatics.generated.h"

UCLASS()
class UZincGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Checks if the game mode of the loaded level is the main menu */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Game Mode", meta=(WorldContext = "WorldContextObject"))
	static bool IsMainMenu(UObject* WorldContextObject)
	{
		AZincMainMenuGameMode* GM = Cast<AZincMainMenuGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
		return GM != nullptr;
	}
	
};
