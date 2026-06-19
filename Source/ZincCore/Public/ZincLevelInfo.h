#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DataTable.h"

#include "ZincLevelInfo.generated.h"

USTRUCT(BlueprintType)
struct FZincLevelInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Info")
	TObjectPtr<UTexture2D> PreviewImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Info")
	FText Description;

};