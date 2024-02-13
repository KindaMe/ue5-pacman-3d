// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimatedTextEntry.generated.h"

USTRUCT(BlueprintType)
struct PACMAN3D_API FAnimatedTextEntry
{
	GENERATED_BODY()

public:
	/** Text to display */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Text"))
	FText Text;

	/**   */
	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta = (DisplayName = "StartAtThisTime", MakeStructureDefaultValue = "0"))
	float StartAtThisTime;

	/** How long is text supposed to be displayed */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "PlaybackTime", MakeStructureDefaultValue = "1"))
	float PlaybackTime;

	/** Text color */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Color"))
	FLinearColor Color;

	FAnimatedTextEntry(): Text(FText::GetEmpty()),
	                      StartAtThisTime(0.f),
	                      PlaybackTime(1.f),
	                      Color(FLinearColor::White)

	{
	}
};

bool operator==(const FAnimatedTextEntry& A, const FAnimatedTextEntry& B);
