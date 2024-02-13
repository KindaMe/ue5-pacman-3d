// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Pacman3D/UI/PauseWidget.h"
#include "PawnController.generated.h"


UCLASS(Abstract)
class PACMAN3D_API APawnController : public APlayerController
{
	GENERATED_BODY()


	///////////////////////////////////
	/// Constructor
	///

	APawnController();


	///////////////////////////////////
	/// Overrides
	///

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


	///////////////////////////////////
	/// Input Mapping
	///

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Mapping")
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Mapping")
	UInputAction* MoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Mapping")
	UInputAction* PauseAction;


	///////////////////////////////////
	/// Input Handling
	///

private:
	void OnMoveTriggered(const FInputActionValue& Value);
	void OnPauseStarted();


	///////////////////////////////////
	/// Pause Menu
	///

protected:
	UPROPERTY(EditDefaultsOnly, Category="Pause Menu")
	TSubclassOf<UPauseWidget> PauseWidget;

	UPROPERTY()
	UPauseWidget* PauseWidgetRef;

	UFUNCTION(BlueprintCallable, Category="Pause Menu")
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category="Pause Menu")
	void UnPauseGame();
};
