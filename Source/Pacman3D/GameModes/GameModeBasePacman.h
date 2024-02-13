// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Pacman3D/Maze/MazeData.h"
#include "Pacman3D/Pawns/Ghosts/MyPawn_Ghost.h"
#include "Pacman3D/Pawns/Pacmans/MyPawn_Pacman.h"
#include "Pacman3D/Pickups/PickupInterface.h"
#include "Pacman3D/UI/InGameWidget.h"
#include "GameModeBasePacman.generated.h"


UCLASS()
class PACMAN3D_API AGameModeBasePacman : public AGameModeBase, public IPickupInterface
{
	GENERATED_BODY()

	///////////////////////////////////
	/// Constructor
	///

	AGameModeBasePacman();


	///////////////////////////////////
	/// Overrides
	///

protected:
	virtual void BeginPlay() override;

	virtual void OnPostLogin(AController* NewPlayer) override;


	///////////////////////////////////
	/// Game States
	///

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Game State")
	void InitGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Game State")
	void PreGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Game State")
	void InGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Game State")
	void PostGame(bool bIsWin);


	///////////////////////////////////
	/// Pacman & Ghosts
	///

public:
	UFUNCTION(BlueprintPure, Category="Pawns")
	void GetCurrentPlayerController(APlayerController*& OutPlayerController) const;

protected:
	UFUNCTION(BlueprintCallable, Category="Pawns")
	void PossessPacman(AMyPawn_Pacman* Pacman);

	UFUNCTION(BlueprintCallable, Category="Pawns")
	void PossessGhosts(TArray<AMyPawn_Ghost*> Ghosts);

	UFUNCTION(BlueprintCallable, Category="Pawns")
	void UnPossessPacman(AMyPawn_Pacman* Pacman) const;

	UFUNCTION(BlueprintCallable, Category="Pawns")
	void UnPossessGhosts(TArray<AMyPawn_Ghost*> Ghosts);

private:
	UPROPERTY()
	APlayerController* CurrentPlayerController;


	///////////////////////////////////
	/// Score
	///

public:
	UFUNCTION(BlueprintPure, Category="Score")
	void GetCurrentScore(int32& OutScore) const;

	UFUNCTION(BlueprintCallable, Category="Score")
	void SetCurrentScore(const int32& Score);

	UFUNCTION(BlueprintCallable, Category="Score")
	void IncreaseCurrentScore(const int32& AddScore);

private:
	UPROPERTY()
	int32 CurrentScore;


	///////////////////////////////////
	/// UI
	///

public:
	UFUNCTION(BlueprintPure, Category="UI")
	void GetInGameWidget(UInGameWidget*& OutWidget) const;

private:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UInGameWidget> InGameWidgetClass;

	UPROPERTY()
	UInGameWidget* InGameWidget;


	///////////////////////////////////
	/// Maze & Maze Spawn
	///

public:
	UFUNCTION(BlueprintPure, Category="Maze")
	void GetMazeTemplate(FMazeData& Template) const;

	UFUNCTION(BlueprintCallable, Category="Maze")
	void SetMazeTemplate(const FMazeData& Template);

	UFUNCTION(BlueprintPure, Category="Maze")
	void GetNavMeshBoundsVolume(ANavMeshBoundsVolume*& OutNavMeshBoundsVolume) const;

private:
	UPROPERTY()
	FMazeData MazeTemplate;

	UPROPERTY()
	ANavMeshBoundsVolume* NavMeshBoundsVolume;

	void FindNavMeshBoundsVolumeInCurrentLevel(ANavMeshBoundsVolume*& OutBoundsVolume);
};
