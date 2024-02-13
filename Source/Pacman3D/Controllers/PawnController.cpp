// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnController.h"

#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"

APawnController::APawnController()
{
	DefaultMappingContext = nullptr;
	MoveAction = nullptr;
	PauseAction = nullptr;
	PauseWidgetRef = nullptr;

	bAutoManageActiveCameraTarget = false;
}

void APawnController::BeginPlay()
{
	Super::BeginPlay();

	if (PauseWidget)
	{
		UUserWidget* Widget = CreateWidget(this, PauseWidget);

		PauseWidgetRef = Cast<UPauseWidget>(Widget);

		if (PauseWidgetRef)
		{
			PauseWidgetRef->OnResumeGame.AddDynamic(this, &APawnController::UnPauseGame);

			PauseWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
			PauseWidgetRef->AddToViewport();
		}
	}

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &APawnController::OnMoveTriggered);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this,
		                                   &APawnController::OnPauseStarted);
	}
}

void APawnController::OnMoveTriggered(const FInputActionValue& Value)
{
	if (GetPawn())
	{
		const FVector2D AxisValue = Value.Get<FVector2D>();

		GetPawn()->AddMovementInput(FVector(AxisValue.X, AxisValue.Y, 0));
	}
}

void APawnController::OnPauseStarted()
{
	if (PauseWidgetRef->IsVisible())
	{
		UnPauseGame();
	}
	else
	{
		PauseGame();
	}
}

void APawnController::PauseGame()
{
	if (PauseWidgetRef)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		PauseWidgetRef->SetVisibility(ESlateVisibility::Visible);

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetWidgetToFocus(PauseWidgetRef->TakeWidget());
		SetInputMode(InputMode);

		SetShowMouseCursor(true);
	}
}

void APawnController::UnPauseGame()
{
	if (PauseWidgetRef)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		PauseWidgetRef->SetVisibility(ESlateVisibility::Collapsed);

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);

		SetShowMouseCursor(false);
	}
}
