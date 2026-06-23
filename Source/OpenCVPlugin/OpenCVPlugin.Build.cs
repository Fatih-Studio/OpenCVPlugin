// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OpenCVPlugin: ModuleRules
{
	public OpenCVPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine"
            }
        );

		PrivateDependencyModuleNames.AddRange(
			new string[] {
                "OpenCVLib",
                "Projects",
                "RenderCore",
                "RHI"
            }
        );
	}
}
