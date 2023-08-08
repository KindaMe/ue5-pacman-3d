// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "CellData.generated.h"

USTRUCT(BlueprintType)
struct PACMAN3D_API FCellData
{
	GENERATED_BODY()

public:
	/** Cell's X Location in grid */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "GridX", MakeStructureDefaultValue = "0"))
	int32 GridX;

	/** Cell's Y Location in grid */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "GridY", MakeStructureDefaultValue = "0"))
	int32 GridY;

	/** Cell's Class */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cell", MakeStructureDefaultValue = "None"))
	TSubclassOf<ACell> Cell;

	FCellData(): GridX(0),
	             GridY(0),
	             Cell(nullptr)
	{
	}
};
