// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn_Ghost.h"


AMyPawn_Ghost::AMyPawn_Ghost()
{
	// Set default values
	FrightenedSpeed = 200.0f;
	DeadSpeed = 1000.0f;
	CurrentMode = EGhostMode::Scatter;
}

void AMyPawn_Ghost::GetCurrentMode(EGhostMode& OutCurrentMode) const
{
	OutCurrentMode = CurrentMode;
}

void AMyPawn_Ghost::SetCurrentMode(const EGhostMode NewCurrentMode)
{
	CurrentMode = NewCurrentMode;
}

void AMyPawn_Ghost::GetScatterBT(UBehaviorTree*& OutScatterBT) const
{
	OutScatterBT = ScatterBT;
}

void AMyPawn_Ghost::GetChaseBT(UBehaviorTree*& OutChaseBT) const
{
	OutChaseBT = ChaseBT;
}

void AMyPawn_Ghost::GetFrightenedBT(UBehaviorTree*& OutFrightenedBT) const
{
	OutFrightenedBT = FrightenedBT;
}

void AMyPawn_Ghost::ResetCurrentSpeedToDefault()
{
	EGhostMode GhostMode;
	GetCurrentMode(GhostMode);

	float Multiplier;
	GetSpeedMultiplier(Multiplier);

	float NewSpeed = 0;

	switch (GhostMode)
	{
	case EGhostMode::Scatter:
	case EGhostMode::Chase:
		GetDefaultSpeed(NewSpeed);
		break;
	case EGhostMode::Frightened:
		GetFrightenedSpeed(NewSpeed);
		break;
	case EGhostMode::Dead:
		GetDeadSpeed(NewSpeed);
		break;
	}

	SetCurrentSpeed(NewSpeed * Multiplier);
}

void AMyPawn_Ghost::GetFrightenedSpeed(float& OutFrightenedSpeed) const
{
	OutFrightenedSpeed = FrightenedSpeed;
}

void AMyPawn_Ghost::GetDeadSpeed(float& OutDeadSpeed) const
{
	OutDeadSpeed = DeadSpeed;
}

void AMyPawn_Ghost::GetFrightenedMaterial(UMaterialInterface*& OutFrightenedMaterial) const
{
	OutFrightenedMaterial = FrightenedMaterial;
}

void AMyPawn_Ghost::GetDeadMaterial(UMaterialInterface*& OutDeadMaterial) const
{
	OutDeadMaterial = DeadMaterial;
}
