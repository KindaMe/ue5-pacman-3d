// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeData.h"

bool operator==(const FMazeData& A, const FMazeData& B)
{
	return A.Width == B.Width &&
		A.Height == B.Height &&
		A.Name.EqualTo(B.Name);
}
