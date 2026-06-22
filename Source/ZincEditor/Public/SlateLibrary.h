#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SlateLibrary.generated.h"

UCLASS()
class USlateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void ShowSlate();

	static FReply OnMyButtonClick();
	
};
