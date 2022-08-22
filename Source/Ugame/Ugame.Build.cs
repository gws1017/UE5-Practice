// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ugame : ModuleRules
{
	public Ugame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayCameras" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.Add(ModuleDirectory); //�����η� ���
	}
}
