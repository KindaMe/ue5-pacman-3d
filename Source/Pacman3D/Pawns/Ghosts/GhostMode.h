// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGhostMode : uint8
{
	Scatter UMETA(DisplayName = "Scatter"),
	Chase UMETA(DisplayName = "Chase"),
	Frightened UMETA(DisplayName = "Frightened"),
	Dead UMETA(DisplayName = "Dead")
};
