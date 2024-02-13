// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstancePacman.h"

#include "SaveGameBase.h"
#include "Kismet/GameplayStatics.h"

UGameInstancePacman::UGameInstancePacman()
{
	MaxLeaderboardEntries = 10;
}

void UGameInstancePacman::Init()
{
	Super::Init();

	USaveGameBase* Save = Cast<USaveGameBase>(UGameplayStatics::LoadGameFromSlot("save", 0));

	if (Save)
	{
		this->Mazes = Save->Mazes;

		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Green,
			FString::Printf(TEXT("Loaded Save | Map Count: %d"), Mazes.Num()));
	}
}

void UGameInstancePacman::SaveGame()
{
	USaveGameBase* NewSave = Cast<USaveGameBase>(UGameplayStatics::CreateSaveGameObject(USaveGameBase::StaticClass()));

	NewSave->Mazes = this->Mazes;

	UGameplayStatics::AsyncSaveGameToSlot(NewSave, "save", 0);
}

void UGameInstancePacman::AddMaze(const FMazeData& Maze)
{
	Mazes.Add(Maze);

	SaveGame();
}

void UGameInstancePacman::LoadGameLevel()
{
	if (GameLevel.IsPending())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), GameLevel);
	}
}

void UGameInstancePacman::LoadEditorLevel()
{
	if (EditorLevel.IsPending())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), EditorLevel);
	}
}

void UGameInstancePacman::LoadMenuLevel()
{
	if (MenuLevel.IsPending())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MenuLevel);
	}
}

void UGameInstancePacman::CheckScoreAgainstLeaderboard(const FMazeData& Maze, const int32 ScoreToCheck,
                                                       bool& bOutIsTopScore, FMazeData& OutMazeToUpdate,
                                                       int32& OutCheckedScore, int32& OutLeaderboardPlace)
{
	for (int32 Index = Maze.TopScores.Num() - 1; Index >= 0; --Index)
	{
		const FLeaderboardEntryData& Entry = Maze.TopScores[Index];

		if (Entry.Score > ScoreToCheck)
		{
			if (Index < MaxLeaderboardEntries - 1)
			{
				bOutIsTopScore = true;
				OutMazeToUpdate = Maze;
				OutCheckedScore = ScoreToCheck;
				OutLeaderboardPlace = Index + 1;
			}
			else
			{
				bOutIsTopScore = false;
				OutMazeToUpdate = FMazeData();
				OutCheckedScore = ScoreToCheck;
				OutLeaderboardPlace = INDEX_NONE;
			}
			return;
		}
	}

	bOutIsTopScore = true;
	OutMazeToUpdate = Maze;
	OutCheckedScore = ScoreToCheck;
	OutLeaderboardPlace = 0;
}

void UGameInstancePacman::AddScoreToLeaderboard(const FMazeData& Maze, const FLeaderboardEntryData& Entry,
                                                const int32 Place,
                                                FMazeData& OutUpdatedMaze, int32& OutPlaceIndex)
{
	const int32 MazeIndex = this->Mazes.Find(Maze);

	if (MazeIndex != INDEX_NONE)
	{
		FMazeData& MazeToUpdate = this->Mazes[MazeIndex];

		MazeToUpdate.TopScores.Insert(Entry, Place);

		while (MazeToUpdate.TopScores.Num() > MaxLeaderboardEntries)
		{
			MazeToUpdate.TopScores.RemoveAt(MazeToUpdate.TopScores.Num() - 1);
		}

		SaveGame();

		OutUpdatedMaze = MazeToUpdate;
		OutPlaceIndex = Place;
	}
	else
	{
		OutUpdatedMaze = FMazeData();
		OutPlaceIndex = INDEX_NONE;
	}
}
