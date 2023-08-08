// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GhostMode.h"
#include "Pacman3D/Pawns/MyPawn.h"

#include "MyPawn_Ghost.generated.h"

UCLASS(Abstract)
class PACMAN3D_API AMyPawn_Ghost : public AMyPawn
{
	GENERATED_BODY()

public:
	AMyPawn_Ghost();

private:
	/** Sub BTree for Scatter ghost mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UBehaviorTree> ScatterBT;

	/** Sub BTree for Chase ghost mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UBehaviorTree> ChaseBT;

	/** Sub BTree for Frightened ghost mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TObjectPtr<UBehaviorTree> FrightenedBT;

	/** Ghost Current Mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	EGhostMode CurrentMode;

	/** Ghost default speed while in Frightened mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Speed")
	float FrightenedSpeed;

	/** Ghost default speed while in Dead mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Speed")
	float DeadSpeed;

	/** Ghost material while in Frightened mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Materials")
	TObjectPtr<UMaterialInterface> FrightenedMaterial;

	/** Ghost material while in Dead mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Materials")
	TObjectPtr<UMaterialInterface> DeadMaterial;

public:
	/** Resets Current Speed to default based on Current ghost Mode */
	virtual void ResetCurrentSpeedToDefault() override;

	/** Returns Current ghost Mode */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetCurrentMode(EGhostMode& OutCurrentMode) const;

	/** Sets Current ghost Mode */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void SetCurrentMode(EGhostMode NewCurrentMode);

	/** Returns Sub BTree for Scatter ghost mode */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetScatterBT(UBehaviorTree*& OutScatterBT) const;

	/** Returns Sub BTree for Chase ghost mode */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetChaseBT(UBehaviorTree*& OutChaseBT) const;

	/** Returns Sub BTree for Frightened ghost mode */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetFrightenedBT(UBehaviorTree*& OutFrightenedBT) const;

	/** Returns Material used when ghost is in Frightened Mode */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetFrightenedMaterial(UMaterialInterface*& OutFrightenedMaterial) const;

	/** Returns Material used when ghost is in Dead Mode */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetDeadMaterial(UMaterialInterface*& OutDeadMaterial) const;

	/** Returns Frightened Speed */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetFrightenedSpeed(float& OutFrightenedSpeed) const;

	/** Returns Dead Speed */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetDeadSpeed(float& OutDeadSpeed) const;
};
