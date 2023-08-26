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


	///////////////////////////////////
	/// Constructor
	///

public:
	AMyPawn_Ghost();


	///////////////////////////////////
	/// AI
	///

public:
	/** Returns Current ghost Mode */
	UFUNCTION(BlueprintPure, Category = "AI")
	void GetCurrentMode(EGhostMode& OutCurrentMode) const;

	/** Sets Current ghost Mode */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetCurrentMode(EGhostMode NewCurrentMode);

	/** Returns Sub BTree for Scatter ghost mode */
	UFUNCTION(BlueprintPure, Category = "AI")
	void GetScatterBT(UBehaviorTree*& OutScatterBT) const;

	/** Returns Sub BTree for Chase ghost mode */
	UFUNCTION(BlueprintPure, Category = "AI")
	void GetChaseBT(UBehaviorTree*& OutChaseBT) const;

	/** Returns Sub BTree for Frightened ghost mode */
	UFUNCTION(BlueprintPure, Category = "AI")
	void GetFrightenedBT(UBehaviorTree*& OutFrightenedBT) const;

private:
	/** Ghost Current Mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|AI")
	EGhostMode CurrentMode;

	/** Sub BTree for Scatter ghost mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|AI")
	TObjectPtr<UBehaviorTree> ScatterBT;

	/** Sub BTree for Chase ghost mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|AI")
	TObjectPtr<UBehaviorTree> ChaseBT;

	/** Sub BTree for Frightened ghost mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|AI")
	TObjectPtr<UBehaviorTree> FrightenedBT;


	///////////////////////////////////
	/// Movement
	///

public:
	/** Resets Current Speed to default based on Current ghost Mode */
	virtual void ResetCurrentSpeedToDefault() override;

	UFUNCTION(BlueprintPure, Category = "Movement")
	void GetFrightenedSpeed(float& OutFrightenedSpeed) const;

	UFUNCTION(BlueprintPure, Category = "Movement")
	void GetDeadSpeed(float& OutDeadSpeed) const;

private:
	/** Ghost default speed while in Frightened mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Movement")
	float FrightenedSpeed;

	/** Ghost default speed while in Dead mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Movement")
	float DeadSpeed;


	///////////////////////////////////
	/// Materials
	///

public:
	/** Returns Material used when ghost is in Frightened Mode */
	UFUNCTION(BlueprintPure, Category = "Materials")
	void GetFrightenedMaterial(UMaterialInterface*& OutFrightenedMaterial) const;

	/** Returns Material used when ghost is in Dead Mode */
	UFUNCTION(BlueprintPure, Category = "Materials")
	void GetDeadMaterial(UMaterialInterface*& OutDeadMaterial) const;

private:
	/** Ghost material while in Frightened mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Materials")
	TObjectPtr<UMaterialInterface> FrightenedMaterial;

	/** Ghost material while in Dead mode */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Materials")
	TObjectPtr<UMaterialInterface> DeadMaterial;
};
