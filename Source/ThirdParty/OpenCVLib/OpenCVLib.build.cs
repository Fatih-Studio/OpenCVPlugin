// Copyright Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;
using UnrealBuildTool;

public class OpenCVLib : ModuleRules
{
	public OpenCVLib(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		
		string PlatformDir = Target.Platform.ToString();
		
        string BinaryPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../Binaries/ThirdParty", PlatformDir));
		string ThirdPartyPath = Path.Combine(ModuleDirectory, "../OpenCVLib");
		string IncPath = Path.Combine(ThirdPartyPath, "include");
		string LibPath = Path.Combine(ThirdPartyPath, "lib", PlatformDir);
		
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicSystemIncludePaths.Add(IncPath);
			PublicIncludePaths.Add(IncPath);
			
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "opencv_world4120.lib"));
			RuntimeDependencies.Add("$(BinaryOutputDir)/opencv_world4120.dll",Path.Combine(ThirdPartyPath, "bin", "Win64", "opencv_world4120.dll"));
			PublicDelayLoadDLLs.Add("opencv_world4120.dll");
			
		}
		
	}
}
