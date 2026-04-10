using UnrealBuildTool;

public class ZincEditor : ModuleRules
{
	public ZincEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;	

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "ZincCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}