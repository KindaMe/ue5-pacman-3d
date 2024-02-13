// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pacman3D/Maze/MazeData.h"
#include "GameInstancePacman.generated.h"


UCLASS(Abstract)
class PACMAN3D_API UGameInstancePacman : public UGameInstance
{ 
	GENERATED_BODY()

	///////////////////////////////////
	/// Constructor
	///

	UGameInstancePacman();


	///////////////////////////////////
	/// Overrides
	///

protected:
	virtual void Init() override;


	///////////////////////////////////
	/// Saves
	///

public:
	UFUNCTION(BlueprintCallable, Category = "Saves")
	void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "Saves")
	void AddMaze(const FMazeData& Maze);

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Saves")
	TArray<FMazeData> Mazes;


	///////////////////////////////////
	/// Levels
	///

public:
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadGameLevel();

	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadEditorLevel();

	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadMenuLevel();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	TSoftObjectPtr<UWorld> GameLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	TSoftObjectPtr<UWorld> EditorLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	TSoftObjectPtr<UWorld> MenuLevel;


	///////////////////////////////////
	/// Leaderboards
	///

public:
	UFUNCTION(BlueprintCallable, Category = "Leaderboard")
	void CheckScoreAgainstLeaderboard(const FMazeData& Maze, int32 ScoreToCheck,
	                                  bool& bOutIsTopScore, FMazeData& OutMazeToUpdate, int32& OutCheckedScore,
	                                  int32& OutLeaderboardPlace);

	UFUNCTION(BlueprintCallable, Category = "Leaderboard")
	void AddScoreToLeaderboard(const FMazeData& Maze, const FLeaderboardEntryData& Entry, int32 Place,
	                           FMazeData& OutUpdatedMaze, int32& OutPlaceIndex);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Leaderboard")
	int32 MaxLeaderboardEntries;
};
