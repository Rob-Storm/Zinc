#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FZincEditor : public IModuleInterface
{
public:
	static inline FZincEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<FZincEditor>("ZincEditor");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ZincEditor");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void RegisterMenuExtensions();

	void OpenMainMenu();
};