#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ReadableData.generated.h"

UCLASS(Abstract, NotBlueprintable)
class UReadableData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/** Title of the note, rendered larger and with a bold fontface if valid */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ReadableData", meta = (MultiLine="false"))
	FText Title = FText::FromString("Title");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ReadableData")
	TObjectPtr<USoundBase> InteractSound;

	/** Override for the actor model used in the world*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ReadableData")
	TObjectPtr<UStaticMesh> ModelOverride = nullptr;		
};
