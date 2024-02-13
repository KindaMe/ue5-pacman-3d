// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimatedTextEntry.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"


UCLASS(Abstract)
class PACMAN3D_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateScore(int32 Score);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DisplayAnimatedText(const TArray<FAnimatedTextEntry>& Entries, bool bIsTopPriority, float& OutTotalPredictedTime);
};
