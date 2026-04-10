#include "ZincEditor.h"
#include "Modules/ModuleManager.h"

#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogZincEditor, Log, All);
DEFINE_LOG_CATEGORY(LogZincEditor);

void FZincEditor::StartupModule()
{
	UE_LOG(LogZincEditor, Log, TEXT("ZincEditor module starting up"));
}

void FZincEditor::ShutdownModule()
{
	UE_LOG(LogZincEditor, Log, TEXT("ZincEditor module shutting down"));
}

IMPLEMENT_GAME_MODULE(FZincEditor, ZincEditor);