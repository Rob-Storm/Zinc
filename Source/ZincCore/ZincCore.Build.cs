using UnrealBuildTool;

public class ZincCore : ModuleRules
{
	public ZincCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;	

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG", "ActorIO", "LevelSequence" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}