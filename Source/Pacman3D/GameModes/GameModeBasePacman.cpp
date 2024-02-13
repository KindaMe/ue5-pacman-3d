// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBasePacman.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Pacman3D/UI/InGameWidget.h"

AGameModeBasePacman::AGameModeBasePacman()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = nullptr;

	CurrentPlayerController = nullptr;
	InGameWidget = nullptr;
	CurrentScore = 0;
	NavMeshBoundsVolume = nullptr;
}

void AGameModeBasePacman::BeginPlay()
{
	Super::BeginPlay();

	FindNavMeshBoundsVolumeInCurrentLevel(NavMeshBoundsVolume);
}

void AGameModeBasePacman::OnPostLogin(AController* NewPlayer)
{
	CurrentPlayerController = Cast<APlayerController>(NewPlayer);

	if (InGameWidgetClass)
	{
		UUserWidget* Widget = CreateWidget(CurrentPlayerController, InGameWidgetClass);

		InGameWidget = Cast<UInGameWidget>(Widget);

		if (InGameWidget)
		{
			InGameWidget->AddToViewport();
		}
	}
}

void AGameModeBasePacman::GetCurrentPlayerController(APlayerController*& OutPlayerController) const
{
	OutPlayerController = CurrentPlayerController;
}

void AGameModeBasePacman::PossessPacman(AMyPawn_Pacman* Pacman)
{
	if (CurrentPlayerController)
	{
		CurrentPlayerController->Possess(Pacman);
	}
}

void AGameModeBasePacman::PossessGhosts(TArray<AMyPawn_Ghost*> Ghosts)
{
	for (AMyPawn_Ghost* Ghost : Ghosts)
	{
		Ghost->SpawnDefaultController();
	}
}

void AGameModeBasePacman::UnPossessPacman(AMyPawn_Pacman* Pacman) const
{
	if (CurrentPlayerController)
	{
		CurrentPlayerController->UnPossess();
	}
}

void AGameModeBasePacman::UnPossessGhosts(TArray<AMyPawn_Ghost*> Ghosts)
{
	for (AMyPawn_Ghost* Ghost : Ghosts)
	{
		Ghost->DetachFromControllerPendingDestroy();
	}
}

void AGameModeBasePacman::IncreaseCurrentScore(const int32& AddScore)
{
	const int32 NewScore = CurrentScore + FMath::Max(AddScore, 0);

	SetCurrentScore(NewScore);
}

void AGameModeBasePacman::GetCurrentScore(int32& OutScore) const
{
	OutScore = CurrentScore;
}

void AGameModeBasePacman::SetCurrentScore(const int32& Score)
{
	CurrentScore = FMath::Max(Score, 0);

	InGameWidget->UpdateScore(CurrentScore);
}

void AGameModeBasePacman::GetInGameWidget(UInGameWidget*& OutWidget) const
{
	OutWidget = InGameWidget;
}

void AGameModeBasePacman::GetMazeTemplate(FMazeData& Template) const
{
	Template = MazeTemplate;
}

void AGameModeBasePacman::SetMazeTemplate(const FMazeData& Template)
{
	MazeTemplate = Template;
}

void AGameModeBasePacman::GetNavMeshBoundsVolume(ANavMeshBoundsVolume*& OutNavMeshBoundsVolume) const
{
	OutNavMeshBoundsVolume = NavMeshBoundsVolume;
}

void AGameModeBasePacman::FindNavMeshBoundsVolumeInCurrentLevel(ANavMeshBoundsVolume*& OutBoundsVolume)
{
	if (AActor* BoundsVolume = UGameplayStatics::GetActorOfClass(GetWorld(), ANavMeshBoundsVolume::StaticClass()))
	{
		OutBoundsVolume = Cast<ANavMeshBoundsVolume>(BoundsVolume);
	}
	else
	{
		OutBoundsVolume = nullptr;
	}
}
