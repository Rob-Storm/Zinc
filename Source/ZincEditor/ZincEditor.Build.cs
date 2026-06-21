using UnrealBuildTool;

public class ZincEditor : ModuleRules
{
	public ZincEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "ZincCore", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "ToolMenus",  "UnrealEd", "EngineSettings"});
	}
}