// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenCVPlugin.h"
#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FOpenCVPluginModule"

void FOpenCVPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	// Construct the DLL path
	FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("OpenCVPlugin"))->GetBaseDir();
	
	FString DllPath = FPaths::Combine(*PluginDir, TEXT("Binaries/Win64/opencv_world4120.dll"));	
	
	//FPlatformProcess::PushDllDirectory(*DllPath);
	OpenCVPluginDLLHandle = FPlatformProcess::GetDllHandle(*DllPath);
	//FPlatformProcess::PopDllDirectory(*OpenCVPluginBinPath);
	
	//cv::unreal::SetMallocAndFree()
	if (!OpenCVPluginDLLHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load OpenCV from: %s"), *DllPath);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("OpenCV loaded successfully"));
	}
	
	//FPlatformProcess::PopDllDirectory();
}

void FOpenCVPluginModule::ShutdownModule()
{	
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	// We do NOT free the DLL handle here. 
	// The OS will clean it up on process exit. 
	// Explicitly freeing third-party DLLs here is a common cause of exit crashes 
	// because Garbage Collection might trigger destructors of OpenCV objects (like cv::VideoCapture) 
	// AFTER this module is unloaded.
	
	/*
	if (OpenCVPluginDLLHandle)
	{
		FPlatformProcess::FreeDllHandle(OpenCVPluginDLLHandle);
		OpenCVPluginDLLHandle = nullptr;
	}
	*/
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOpenCVPluginModule, OpenCVPlugin)
