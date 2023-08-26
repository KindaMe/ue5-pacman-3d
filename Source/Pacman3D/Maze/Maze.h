// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/ArrowComponent.h>
#include "MazeData.h"
#include "Pacman3D/Pawns/MyPawn.h"
#include "Pacman3D/Pawns/Ghosts/MyPawn_Ghost.h"
#include "Pacman3D/Pawns/Pacmans/MyPawn_Pacman.h"
#include "Pacman3D/Pickups/Pickup.h"

#include "Maze.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAnyPickupCollected, APickup*, Pickup, int, Score, int, PickupsLeft);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGhostIsDead, AMyPawn_Ghost*, Ghost, bool, bIsDead);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPacmanIsDead, AMyPawn_Pacman*, Pacman, bool, bIsDead);

UCLASS(Abstract)
class PACMAN3D_API AMaze : public AActor
{
	GENERATED_BODY()


	///////////////////////////////////
	/// Constructor
	///
	
public:
	AMaze();


	///////////////////////////////////
	/// Overrides
	///
	
protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;


	///////////////////////////////////
	/// Delegates & Events
	///
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAnyPickupCollected OnAnyPickupCollected;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGhostIsDead OnGhostIsDead;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPacmanIsDead OnPacmanIsDead;

	/** Function that gets triggered when a pickup item is collected. */
	UFUNCTION(Category = "Events")
	void OnPickupCollected(APickup* Pickup, int Score);

	/** Function that gets triggered when a ghost pawn dies. */
	UFUNCTION(Category = "Events")
	void OnGhostPawnIsDead(AMyPawn* Pawn, bool bIsDead);

	/** Function that gets triggered when Pacman dies. */
	UFUNCTION(Category = "Events")
	void OnPacmanPawnIsDead(AMyPawn* Pawn, bool bIsDead);


	///////////////////////////////////
	/// Maze
	///
	
public:
	/** Updates MazeData.Cells based on current maze layout */
	UFUNCTION(BlueprintCallable, Category = "Maze")
	void SaveMazeTemplate();

	/** Sets maze template data */
	UFUNCTION(BlueprintCallable, Category = "Maze")
	void SetMazeTemplate(const FMazeData& NewMazeTemplate);

	/** Returns maze template data */
	UFUNCTION(BlueprintPure, Category = "Maze")
	void GetMazeTemplate(FMazeData& OutMazeTemplate) const;

	/** Returns world actual maze size based on Cell Size */
	UFUNCTION(BlueprintPure, Category = "Maze")
	FVector GetActualMazeSize() const;

private:
	/** Maze Template Data */
	UPROPERTY(EditAnywhere, Category = "Maze")
	FMazeData MazeData;

	/** Temporary Cell storage for template saving purposes */
	UPROPERTY()
	TArray<UChildActorComponent*> Cells;

	/** Default Size of Cell actor */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Maze")
	FVector CellSize = FVector(100.0f, 100.0f, 100.0f);


	///////////////////////////////////
	/// Camera
	///
	
public:
	/** Resets the Spring Arm's position and length based on the Maze actor's dimensions. */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ResetCameraLocation();

	/** Changes Spring Arm's X/Y location based on the direction parameter passed to the function. */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ChangeCameraLocation(FVector2D InputDirection);

	/** Increases or decreases the Spring Arm's length based on the direction parameter passed to the function. */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ChangeCameraDistance(float InputDirection);

private:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;


	///////////////////////////////////
	/// Pickups
	///
	
public:
	/** Returns amount of pickups left */
	UFUNCTION(BlueprintPure, Category = "Pickups")
	void GetAmountOfPickupsLeft(int32& OutPickupsLeft) const;

	/** Returns array of pickup references */
	UFUNCTION(BlueprintPure, Category = "Pickups")
	void GetPickups(TArray<APickup*>& OutPickups) const;

private:
	/** Pickup References */
	UPROPERTY()
	TArray<APickup*> PickupActors;


	///////////////////////////////////
	/// Ghosts & Pacman
	///
	
public:
	/** Returns array of ghost references */
	UFUNCTION(BlueprintPure, Category = "Ghosts")
	void GetGhosts(TArray<AMyPawn_Ghost*>& OutGhosts) const;

	/** Returns pacman reference */
	UFUNCTION(BlueprintPure, Category = "Pacman")
	void GetPacman(AMyPawn_Pacman*& OutPacman) const;

private:
	/** Ghost References */
	UPROPERTY()
	TArray<AMyPawn_Ghost*> GhostPawns;

	/** Pacman Reference */
	UPROPERTY()
	TObjectPtr<AMyPawn_Pacman> PacmanPawn;


	///////////////////////////////////
	/// Other Components
	///
	
private:
	UPROPERTY()
	TObjectPtr<UArrowComponent> Arrow;
};
