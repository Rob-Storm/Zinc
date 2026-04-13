#pragma once

#include "CoreMinimal.h"
#include "ReadableData.h"

#include "PictureData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UPictureData : public UReadableData
{
	GENERATED_BODY()

public:

	/** Image resolution should not exceed 1280x720 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PictureData")
	TArray<UTexture2D*> Pictures;
	
};
