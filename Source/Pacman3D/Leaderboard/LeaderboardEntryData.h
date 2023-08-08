// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeaderboardEntryData.generated.h"

USTRUCT(BlueprintType)
struct PACMAN3D_API FLeaderboardEntryData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	int32 Score;

	FLeaderboardEntryData(): PlayerName(TEXT("")),
	                         Score(0)
	{
	}
};
