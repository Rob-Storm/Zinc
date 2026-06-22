#include "ZincEditor.h"
#include "Modules/ModuleManager.h"

#include "ToolMenus.h"
#include "GameMapsSettings.h"
#include "FileHelpers.h"

#include "SlateLibrary.h"

#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogZincEditor, Log, All);
DEFINE_LOG_CATEGORY(LogZincEditor);

void FZincEditor::StartupModule()
{
	UE_LOG(LogZincEditor, Log, TEXT("ZincEditor module starting up"));

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FZincEditor::RegisterMenuExtensions));
}

void FZincEditor::ShutdownModule()
{
	UE_LOG(LogZincEditor, Log, TEXT("ZincEditor module shutting down"))

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

void FZincEditor::RegisterMenuExtensions()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.ModesToolBar");

	FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("File");

	FToolMenuEntry Entry = FToolMenuEntry::InitToolBarButton
	(
		TEXT("OpenMainMenuLevel"),
		FExecuteAction::CreateLambda([this]()
		{
			OpenMainMenu();
		}),
		INVTEXT("Open Main Menu Level"),
		INVTEXT("Opens the GameDefaultMap, which should be the main menu"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.World") // don't even ask me how long it took to find this
		
	);

	Entry.StyleNameOverride = "CalloutToolbar";

	ToolbarSection.AddEntry(Entry);


	UToolMenu* WindowMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");

	FToolMenuSection& SlateSection = WindowMenu->AddSection
	(
		"SlateTesting", 
		INVTEXT("Slate Testing"), 
		FToolMenuInsert("Tools", EToolMenuInsertType::After)
	);

	FToolMenuEntry SlateEntry = FToolMenuEntry::InitMenuEntry
	(
		"SlateWindow",
		INVTEXT("Slate Window"),
		INVTEXT("Opens the custom slate window"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "SceneOutliner.World"),
		FExecuteAction::CreateLambda([this]()
		{
			USlateLibrary::ShowSlate();
		})
	);

	SlateSection.AddEntry(SlateEntry);
}

void FZincEditor::OpenMainMenu()
{
	 if (FEditorFileUtils::SaveDirtyPackages(true, true, true))
	 {
	 	UEditorLoadingAndSavingUtils::LoadMap(UGameMapsSettings::GetGameDefaultMap());
	 }

}

IMPLEMENT_GAME_MODULE(FZincEditor, ZincEditor);