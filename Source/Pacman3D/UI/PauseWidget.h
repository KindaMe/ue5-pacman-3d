// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResumeGame);

UCLASS(Abstract)
class PACMAN3D_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()


	///////////////////////////////////
	/// Delegates & Events
	///

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FOnResumeGame OnResumeGame;
};
