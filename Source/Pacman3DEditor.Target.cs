// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Pacman3DEditorTarget : TargetRules
{
	public Pacman3DEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange(new[] { "Pacman3D" });
	}
}