// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set default values
	SpeedMultiplier = 1.0f;
	bIsDead = false;
	DefaultSpeed = 500.0f;

	// Set default components
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	CapsuleCollision->SetCapsuleRadius(49.9f);
	CapsuleCollision->SetCapsuleHalfHeight(49.9f);
	CapsuleCollision->SetCollisionProfileName(TEXT("Pawn"));
	CapsuleCollision->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
	CapsuleCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CapsuleCollision;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(CapsuleCollision);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName(TEXT("CharacterMesh"));
	StaticMesh->SetupAttachment(CapsuleCollision);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CapsuleCollision);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ResetMeshMaterialToDefault();
	ResetCurrentSpeedToDefault();
}


void AMyPawn::GetDefaultSpeed(float& OutDefaultSpeed) const
{
	OutDefaultSpeed = DefaultSpeed;
}

void AMyPawn::GetCurrentSpeed(float& OutCurrentSpeed) const
{
	OutCurrentSpeed = FloatingPawnMovement->MaxSpeed;
}

void AMyPawn::SetCurrentSpeed(const float NewSpeed)
{
	if (FloatingPawnMovement)
	{
		FloatingPawnMovement->MaxSpeed = NewSpeed;
	}
}

void AMyPawn::ResetCurrentSpeedToDefault()
{
	float Speed;
	GetDefaultSpeed(Speed);

	float Multiplier;
	GetSpeedMultiplier(Multiplier);

	SetCurrentSpeed(Speed * Multiplier);
}

void AMyPawn::GetSpeedMultiplier(float& OutSpeedMultiplier) const
{
	OutSpeedMultiplier = SpeedMultiplier;
}

void AMyPawn::SetSpeedMultiplier(const float NewSpeedMultiplier)
{
	this->SpeedMultiplier = NewSpeedMultiplier;
	ResetCurrentSpeedToDefault();
}

void AMyPawn::SetIsDead(const bool IsDead)
{
	if (bIsDead != IsDead)
	{
		bIsDead = IsDead;
		OnPawnIsDead.Broadcast(this, IsDead);
		OnSetIsDead(IsDead);
	}
}

void AMyPawn::SetMeshMaterial(UMaterialInterface* NewMaterial)
{
	if (StaticMesh)
	{
		StaticMesh->SetMaterial(0, NewMaterial);
	}
}

void AMyPawn::ResetMeshMaterialToDefault()
{
	SetMeshMaterial(DefaultStaticMeshMaterial);
}
