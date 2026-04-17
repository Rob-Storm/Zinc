#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ProcessChecker.generated.h"

UCLASS()
class UProcessChecker : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Process")
	static bool IsEditor()
	{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
	}
	
};
