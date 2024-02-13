// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cells/CellData.h"
#include "Pacman3D/Leaderboard/LeaderboardEntryData.h"
#include "MazeData.generated.h"

USTRUCT(BlueprintType)
struct PACMAN3D_API FMazeData
{
	GENERATED_BODY()

public:
	/** Width of the maze */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Width", MakeStructureDefaultValue = "0"))
	int32 Width;

	/** Height of the maze */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Height", MakeStructureDefaultValue = "0"))
	int32 Height;

	/**  Array with data of each of the maze's cells */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cells"))
	TArray<FCellData> Cells;

	/**  Name of the maze */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Name"))
	FText Name;
	/**  Array of top scores */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "TopScores"))
	TArray<FLeaderboardEntryData> TopScores;

	FMazeData(): Width(0),
	             Height(0),
	             Name(FText::GetEmpty())
	{
	}
};

bool operator==(const FMazeData& A, const FMazeData& B);
