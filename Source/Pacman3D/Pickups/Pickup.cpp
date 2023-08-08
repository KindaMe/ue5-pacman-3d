// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"

#include "Pacman3D/Audio/AudioManager.h",
#include "PickupInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Pacman3D/Pawns/Pacmans/MyPawn_Pacman.h"


APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set default values
	Score = 10;

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(
		TEXT("/Game/PacmanGame/Sound/PickupDefault.PickupDefault"));

	if (SoundAsset.Succeeded())
	{
		PickupSound = SoundAsset.Object;
	}

	// Set default components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	CapsuleCollision->SetRelativeLocation(FVector(0, 0, 50));
	CapsuleCollision->SetCapsuleHalfHeight(25);
	CapsuleCollision->SetCapsuleRadius(25);
	CapsuleCollision->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(CapsuleCollision);
}


void APickup::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
}


void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AMyPawn_Pacman::StaticClass()))
	{
		AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
		if (GameMode && GameMode->GetClass()->ImplementsInterface(UPickupInterface::StaticClass()))
		{
			ApplyPickupEffects(GameMode);
		}

		OnCollected.Broadcast(this, Score);

		const UGameInstance* GameInstance = GetWorld()->GetGameInstance();

		if (UAudioManagerSubsystem* AudioManagerSubsystem = GameInstance->GetSubsystem<UAudioManagerSubsystem>())
		{
			AudioManagerSubsystem->PlayPickupSound(PickupSound);
		}

		Destroy();
	}
}

void APickup::GetScore(int32& OutScore) const
{
	OutScore = Score;
}
