#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Music.generated.h"

UCLASS()
class UMusic : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<USoundBase> MusicTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	int32 Priority = 0;
	
};
