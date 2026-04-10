using UnrealBuildTool;

public class ZincTarget : TargetRules
{
	public ZincTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "ZincCore" } );
	}
}