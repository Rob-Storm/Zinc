#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericWindow.h"

#include "GraphicSettings.generated.h"


/** This struct is used to confirm graphics settings after applying to ensure the user can still interact with the game (e.g. the UI scale is too small and can be reverted automatically) */

USTRUCT(BlueprintType)
struct FGraphicSettings
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GraphicSettings")
	FIntPoint Resolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GraphicSettings")
	float UIScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GrahpicSettings")
	TEnumAsByte<EWindowMode::Type> WindowMode = EWindowMode::Type::Fullscreen;

};