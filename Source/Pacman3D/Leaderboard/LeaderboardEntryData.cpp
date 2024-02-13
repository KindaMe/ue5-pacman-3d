// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardEntryData.h"

bool operator==(const FLeaderboardEntryData& A, const FLeaderboardEntryData& B)
{
	return A.PlayerName.Equals(B.PlayerName) && A.Score == B.Score;
}
