#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/PackageName.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "FileUtilities.generated.h"

UCLASS()
class UFileUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="File")
	static bool DoesPackageExist(const FString& PackageName)
	{
		return FPackageName::DoesPackageExist(PackageName);
	}

	/** Checks if a map exists from its asset name */
	UFUNCTION(BlueprintCallable, Category="File")
	static bool DoesMapExist(const FString& MapName);

	/** Returns an array of FStrings for every map that is loaded from the pak files */
	UFUNCTION(BlueprintCallable, Category="File")
	static TArray<FString> GetInstalledMaps();
	
};