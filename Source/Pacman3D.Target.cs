// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Pacman3DTarget : TargetRules
{
	public Pacman3DTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange(new[] { "Pacman3D" });
	}
}