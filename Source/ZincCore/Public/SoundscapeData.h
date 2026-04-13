#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "SoundscapeData.generated.h"

UCLASS()
class USoundscapeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZincCore")
	FString SoundscapeName = TEXT("Soundscape Name");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soundscape")
	TObjectPtr<USoundBase> MainLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soundscape")
	TArray<USoundBase*> OneShotSounds;
	
};
