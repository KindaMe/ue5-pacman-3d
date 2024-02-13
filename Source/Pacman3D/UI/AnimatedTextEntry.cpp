// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatedTextEntry.h"

bool operator==(const FAnimatedTextEntry& A, const FAnimatedTextEntry& B)
{
	return A.Text.EqualTo(B.Text) &&
		A.StartAtThisTime == B.StartAtThisTime &&
		A.PlaybackTime == B.PlaybackTime &&
		A.Color == B.Color;
}
