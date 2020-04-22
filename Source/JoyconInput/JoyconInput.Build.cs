using UnrealBuildTool;
using System.IO;

public class JoyconInput : ModuleRules
{
	public JoyconInput(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableUndefinedIdentifierWarnings = false;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Classes"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

		PublicIncludePaths.AddRange(new string[] { });

		PrivateIncludePaths.AddRange(new string[] { });

		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

		PrivateDependencyModuleNames.AddRange(new string[] {
			"CoreUObject",
			"Engine",
			"Slate",
			"ApplicationCore",
			"InputCore",
			"InputDevice"
		});

		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
