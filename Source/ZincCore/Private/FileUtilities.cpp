#include "FileUtilities.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "AssetRegistry/AssetRegistryModule.h"

bool UFileUtilities::DoesMapExist(const FString& MapName)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    TArray<FAssetData> Maps;
    AssetRegistry.GetAssetsByClass(UWorld::StaticClass()->GetClassPathName(),Maps);

    for (const FAssetData& Asset : Maps)
    {
        if (Asset.AssetName.ToString() == MapName)
        {
            return true;
        }
    }

    return false;
}

TArray<FString> UFileUtilities::GetInstalledMaps()
{
	TArray<FString> MapNames;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    TArray<FAssetData> Maps;
    AssetRegistry.GetAssetsByClass(UWorld::StaticClass()->GetClassPathName(),Maps);

    for (const FAssetData& Asset : Maps)
    {
    	MapNames.Add(Asset.AssetName.ToString());
    }

    return MapNames;

}