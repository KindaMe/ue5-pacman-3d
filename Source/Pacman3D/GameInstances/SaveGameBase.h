// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Pacman3D/Maze/MazeData.h"
#include "SaveGameBase.generated.h"


UCLASS()
class PACMAN3D_API USaveGameBase : public USaveGame
{
	GENERATED_BODY()

	///////////////////////////////////
	/// Save Data
	///

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FMazeData> Mazes;
};
