using UnrealBuildTool;

public class ZincCore : ModuleRules
{
	public ZincCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "ActorIO", "LevelSequence" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG", "SlateCore", "Slate" });
	}
}