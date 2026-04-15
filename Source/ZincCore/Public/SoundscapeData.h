#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "SoundscapeData.generated.h"

USTRUCT(BlueprintType)
struct FOneShotData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OneShot")
	TObjectPtr<USoundBase> SoundAsset;

	/** If false, the sound will be 2D and have random panning */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OneShot")
	bool IsWorldSound = true;

	/** Minimum pan amount. -1 = fully left, 1 = fully right, 0 = center */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OneShot", meta=(ClampMin=-1, ClampMax=1, UIMin=-1, UIMax=1, EditCondition="!IsWorldSound"))
	float MinPan = -1.f;

	/** Maximum pan amount. -1 = fully left, 1 = fully right, 0 = center */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OneShot", meta=(ClampMin=-1, ClampMax=1, UIMin=-1, UIMax=1, EditCondition="!IsWorldSound"))
	float MaxPan = 1.f;

};

UCLASS()
class USoundscapeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZincCore")
	FString SoundscapeName = TEXT("Soundscape Name");

	/** The backing loop that will always be heard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soundscape")
	TObjectPtr<USoundBase> MainLoop;

	/** Sounds you want to be played randomly around the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soundscape")
	TArray<FOneShotData> OneShotSounds;

	/** The time before the first OneShot sound is played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soundscape")
	float InitialOneShotDelay = 5.f;

	/** The time between subsequent OneShot sounds being played. This value is added to the duration of the OneShot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soundscape")
	float OneShotDelayVariance = 10.f;
	
};
