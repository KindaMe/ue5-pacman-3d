// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze.h"

#include "Pacman3D/Pawns/Pacmans/MyPawn_Pacman.h"


// Sets default values
AMaze::AMaze()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set default components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetRelativeLocation(FVector(0, 0, 100));
	Arrow->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-90, 0, 0));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetFieldOfView(100);
	Camera->SetupAttachment(SpringArm);
}


void AMaze::BeginPlay()
{
	Super::BeginPlay();

	// Create bindings for pickup actors
	for (APickup* Pickup : PickupActors)
	{
		if (Pickup)
		{
			Pickup->OnCollected.AddDynamic(this, &AMaze::OnPickupCollected);
		}
	}

	// Create bindings for ghost pawns
	for (AMyPawn_Ghost* Ghost : GhostPawns)
	{
		if (Ghost)
		{
			Ghost->OnPawnIsDead.AddDynamic(this, &AMaze::OnGhostPawnIsDead);
		}
	}

	// Create binding for pacman pawn
	if (PacmanPawn)
	{
		PacmanPawn->OnPawnIsDead.AddDynamic(this, &AMaze::OnPacmanPawnIsDead);
	}
}

void AMaze::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Clear any existing cells (in case this is a re-construction)
	for (int32 i = Cells.Num() - 1; i >= 0; --i)
	{
		UChildActorComponent* Cell = Cells[i];
		if (IsValid(Cell))
		{
			// if (Cell->IsRegistered())
			// 	Cell->UnregisterComponent();

			Cell->DestroyComponent();
			Cells.RemoveAt(i);
		}
	}

	PickupActors.Empty();
	GhostPawns.Empty();
	PacmanPawn = nullptr;

	// Create child actors based on maze template
	for (const FCellData& CellData : MazeData.Cells)
	{
		UChildActorComponent* CellComponent = NewObject<UChildActorComponent>(this);

		const FVector RelativeLocation = FVector(CellData.GridX * CellSize.X, CellData.GridY * CellSize.Y, 0);
		CellComponent->SetRelativeLocation(RelativeLocation);

		CellComponent->SetChildActorClass(CellData.Cell);

		CellComponent->SetupAttachment(RootComponent);

		CellComponent->RegisterComponent();

		Cells.Add(CellComponent);

		// Check if the child actor has the required components
		if (const ACell* Cell = Cast<ACell>(CellComponent->GetChildActor()))
		{
			AActor* Actor;
			Cell->GetCellChildActor(Actor);

			if (Actor)
			{
				// Check if it's a Ghost
				if (AMyPawn_Ghost* Ghost = Cast<AMyPawn_Ghost>(Actor))
				{
					GhostPawns.Add(Ghost);
				}
				// Check if it's a Pickup
				else if (APickup* Pickup = Cast<APickup>(Actor))
				{
					PickupActors.Add(Pickup);
				}
				// Check if it's Pacman
				else if (AMyPawn_Pacman* Pacman = Cast<AMyPawn_Pacman>(Actor))
				{
					PacmanPawn = Pacman;
				}
			}
		}
	}

	ResetCameraLocation();
}

void AMaze::OnPickupCollected(APickup* Pickup, const int Score)
{
	// Unbind the delegate from this pickup
	Pickup->OnCollected.RemoveDynamic(this, &AMaze::OnPickupCollected);

	// Remove this pickup from PickupActors array
	PickupActors.Remove(Pickup);

	OnAnyPickupCollected.Broadcast(Pickup, Score, PickupActors.Num());

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Pickup Collected."));
}

void AMaze::OnGhostPawnIsDead(AMyPawn* Pawn, const bool bIsDead)
{
	if (AMyPawn_Ghost* Ghost = Cast<AMyPawn_Ghost>(Pawn))
	{
		OnGhostIsDead.Broadcast(Ghost, bIsDead);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Ghost bIsDead changed."));
}

void AMaze::OnPacmanPawnIsDead(AMyPawn* Pawn, const bool bIsDead)
{
	if (AMyPawn_Pacman* Pacman = Cast<AMyPawn_Pacman>(Pawn))
	{
		OnPacmanIsDead.Broadcast(Pacman, bIsDead);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Pacman bIsDead changed."));
}

void AMaze::SaveMazeTemplate()
{
	MazeData.Cells.Empty();

	for (const UChildActorComponent* Cell : Cells)
	{
		FCellData CellData;
		CellData.Cell = Cell->GetChildActorClass();
		const FVector Location = Cell->GetRelativeLocation();
		CellData.GridX = Location.X / CellSize.X;
		CellData.GridY = Location.Y / CellSize.Y;
		MazeData.Cells.Add(CellData);
	}
}

void AMaze::SetMazeTemplate(const FMazeData& NewMazeTemplate)
{
	MazeData = NewMazeTemplate;
}

void AMaze::GetMazeTemplate(FMazeData& OutMazeTemplate) const
{
	OutMazeTemplate = MazeData;
}

FVector AMaze::GetActualMazeSize() const
{
	return FVector(CellSize.X * (MazeData.Height - 1), CellSize.Y * (MazeData.Width - 1), CellSize.Z);
}

void AMaze::ResetCameraLocation()
{
	// Calculating an actual maze size
	const FVector ActualMazeSize(GetActualMazeSize());

	// Spring Arm length buffer
	constexpr float Buffer = 1.0f; // Increase or decrease as needed

	// Setting Spring Arm length
	SpringArm->TargetArmLength = FMath::Max(ActualMazeSize.X, ActualMazeSize.Y) * Buffer;

	// Centering Spring Arm
	const FVector MazeCenter(ActualMazeSize / 2);
	SpringArm->SetRelativeLocation(MazeCenter);
}

void AMaze::ChangeCameraLocation(FVector2D InputDirection)
{
	// Normalize the input direction.
	InputDirection.Normalize();

	// Getting the actual maze size.
	const FVector ActualMazeSize(GetActualMazeSize());

	// Get the world delta seconds.
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	// Calculate the movement based on the direction, speed, and delta time.
	const FVector Movement = FVector(InputDirection.X, InputDirection.Y, 0.0f) * 1500 * DeltaTime;

	// Calculate the new location for the camera arm.
	FVector NewLocation = SpringArm->GetComponentLocation() + Movement;

	// Clamp the values based on maze size.
	NewLocation.X = FMath::Clamp(NewLocation.X, 0, ActualMazeSize.X);
	NewLocation.Y = FMath::Clamp(NewLocation.Y, 0, ActualMazeSize.Y);

	// Set the camera arm's new location.
	SpringArm->SetWorldLocation(NewLocation);
}

void AMaze::ChangeCameraDistance(float InputDirection)
{
	// Getting the actual maze size.
	const FVector ActualMazeSize(GetActualMazeSize());

	// Getting the Optimal Camera Distance from maze.
	const float OptimalDistance = FMath::Max(ActualMazeSize.X, ActualMazeSize.Y);

	// Define the minimum and maximum arm lengths.
	const float MinArmLength = OptimalDistance * .5f;
	const float MaxArmLength = OptimalDistance * 1.5f;

	// Calculate new arm length.
	const float NewLength = SpringArm->TargetArmLength + (-1 * InputDirection * 250);

	// Set the camera arm's length.
	SpringArm->TargetArmLength = FMath::Clamp(NewLength, MinArmLength, MaxArmLength);
}

void AMaze::GetAmountOfPickupsLeft(int32& OutPickupsLeft) const
{
	OutPickupsLeft = PickupActors.Num();
}

void AMaze::GetPickups(TArray<APickup*>& OutPickups) const
{
	OutPickups = PickupActors;
}

void AMaze::GetGhosts(TArray<AMyPawn_Ghost*>& OutGhosts) const
{
	OutGhosts = GhostPawns;
}

void AMaze::GetPacman(AMyPawn_Pacman*& OutPacman) const
{
	OutPacman = PacmanPawn;
}


