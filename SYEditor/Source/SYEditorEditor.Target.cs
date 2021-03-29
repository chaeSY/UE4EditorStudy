// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SYEditorEditorTarget : TargetRules
{
	public SYEditorEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		//ExtraModuleNames.AddRange( new string[] { "SYEditor" } );
		ExtraModuleNames.AddRange( new string[] { "SYEditor", "SYEditorExtension" } );
    }
}
