#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FZincCore : public IModuleInterface
{
public:
	static inline FZincCore& Get()
	{
		return FModuleManager::LoadModuleChecked<FZincCore>("ZincCore");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ZincCore");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};