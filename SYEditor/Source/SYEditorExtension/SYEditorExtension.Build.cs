// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SYEditorExtension : ModuleRules
{
	public SYEditorExtension(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "UnrealEd", "LevelEditor", "SlateCore", "Slate", "SYEditor", "Engine", "AdvancedPreviewScene", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
