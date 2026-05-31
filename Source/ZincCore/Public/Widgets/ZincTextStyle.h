#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Fonts/SlateFontInfo.h"
#include "Engine/DataAsset.h"

#include "ZincTextStyle.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UZincTextStyle : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Font")
	FSlateFontInfo FontStyle;
	
};