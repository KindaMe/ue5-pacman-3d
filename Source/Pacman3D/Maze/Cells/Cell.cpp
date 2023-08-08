// Fill out your copyright notice in the Description page of Project Settings.

#include "Cell.h"


// Sets default values
ACell::ACell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set default components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActorComponent"));
	ChildActorComponent->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
}

void ACell::GetCellChildActor(AActor*& OutChildActor) const
{
	OutChildActor = nullptr;
	if (ChildActorComponent)
	{
		OutChildActor = ChildActorComponent->GetChildActor();
	}
}

void ACell::ChangeCellParentComponentClass(const TSubclassOf<ACell> NewParentClass, bool& bOutSuccess)
{
	if (UChildActorComponent* CellParentComponent = Cast<UChildActorComponent>(GetParentComponent()))
	{
		if (NewParentClass && CellParentComponent->GetChildActorClass() != NewParentClass)
		{
			CellParentComponent->SetChildActorClass(NewParentClass);
			bOutSuccess = true;
			return;
		}
	}
	bOutSuccess = false;
}

void ACell::GetCellType(ECellType& OutCellType) const
{
	OutCellType = CellType;
}

void ACell::GetDisplayName(FName& OutDisplayName) const
{
	OutDisplayName = DisplayName;
}
