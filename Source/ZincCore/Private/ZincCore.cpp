#include "ZincCore.h"
#include "Modules/ModuleManager.h"

#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogZincCore, Log, All);
DEFINE_LOG_CATEGORY(LogZincCore);

void FZincCore::StartupModule()
{
	UE_LOG(LogZincCore, Log, TEXT("ZincCore module starting up"));
}

void FZincCore::ShutdownModule()
{
	UE_LOG(LogZincCore, Log, TEXT("ZincCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, ZincCore, "ZincCore");