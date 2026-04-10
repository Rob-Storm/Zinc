using UnrealBuildTool;

public class ZincEditorTarget : TargetRules
{
	public ZincEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "ZincCore" } );
	}
}