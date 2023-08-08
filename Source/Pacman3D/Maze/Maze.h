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

public:
	AMaze();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	/**  */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAnyPickupCollected OnAnyPickupCollected;

	/**  */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGhostIsDead OnGhostIsDead;

	/**  */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPacmanIsDead OnPacmanIsDead;

	/**  */
	UFUNCTION(Category = "Default")
	void OnPickupCollected(APickup* Pickup, int Score);

	/**  */
	UFUNCTION(Category = "Default")
	void OnGhostPawnIsDead(AMyPawn* Pawn, bool bIsDead);

	/**  */
	UFUNCTION(Category = "Default")
	void OnPacmanPawnIsDead(AMyPawn* Pawn, bool bIsDead);

	/** Updates MazeData.Cells based on current maze layout */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void SaveMazeTemplate();

	/** Resets the Spring Arm's position and length based on the Maze actor's dimensions. */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void ResetCameraLocation();

	/** Changes Spring Arm's X/Y location based on the direction parameter passed to the function. */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void ChangeCameraLocation(FVector2D InputDirection);

	/** Increases or decreases the Spring Arm's length based on the direction parameter passed to the function. */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void ChangeCameraDistance(float InputDirection);

	/** Returns amount of pickups left */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetAmountOfPickupsLeft(int32& OutPickupsLeft) const;

	/** Returns array of pickup references */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetPickups(TArray<APickup*>& OutPickups) const;

	/** Returns array of ghost references */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetGhosts(TArray<AMyPawn_Ghost*>& OutGhosts) const;

	/** Returns pacman reference */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetPacman(AMyPawn_Pacman*& OutPacman) const;

	/** Sets maze template data */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void SetMazeTemplate(const FMazeData& NewMazeTemplate);

	/** Returns maze template data */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetMazeTemplate(FMazeData& OutMazeTemplate) const;

	/** Returns world actual maze size based */
	UFUNCTION(BlueprintPure, Category = "Default")
	FVector GetActualMazeSize() const;

private:
	/**  */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UCameraComponent> Camera;

	/**  */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<USpringArmComponent> SpringArm;

	/**  */
	UPROPERTY()
	TObjectPtr<UArrowComponent> Arrow;

	/**  */
	UPROPERTY(EditAnywhere, Category = "Default")
	FMazeData MazeData;

	/**  */
	UPROPERTY()
	TArray<AMyPawn_Ghost*> GhostPawns;

	/**  */
	UPROPERTY()
	TArray<APickup*> PickupActors;

	/**  */
	UPROPERTY()
	TObjectPtr<AMyPawn_Pacman> PacmanPawn;

	/**  */
	UPROPERTY()
	TArray<UChildActorComponent*> Cells;

	/**  */
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	FVector CellSize = FVector(100.0f, 100.0f, 100.0f);
};
