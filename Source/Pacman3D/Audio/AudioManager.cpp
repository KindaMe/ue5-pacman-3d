// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


void UAudioManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// SoundConcurrencyUI = NewObject<USoundConcurrency>(this);
	// if (SoundConcurrencyUI)
	// {
	// 	SoundConcurrencyUI->Concurrency.MaxCount = 1;
	// 	SoundConcurrencyUI->Concurrency.bLimitToOwner = false;
	// 	SoundConcurrencyUI->Concurrency.ResolutionRule = EMaxConcurrentResolutionRule::StopOldest;
	// }


	//Initialize Sounds
	ButtonHoverSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,
	                                                     TEXT("/Game/PacmanGame/Sound/ButtonHover.ButtonHover")));

	ButtonClickSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,
	                                                     TEXT("/Game/PacmanGame/Sound/ButtonClick.ButtonClick")));

	MainLoopSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,
	                                                  TEXT("/Game/PacmanGame/Sound/MainLoop.MainLoop")));

	SuccessSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,
	                                                 TEXT("/Game/PacmanGame/Sound/Success.Success")));

	FailSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,
	                                              TEXT("/Game/PacmanGame/Sound/Fail.Fail")));

	PowerUpStartSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,
	                                                      TEXT("/Game/PacmanGame/Sound/PowerUpStart.PowerUpStart")));

	PowerUpEndSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,
	                                                    TEXT("/Game/PacmanGame/Sound/PowerUpEnd.PowerUpEnd")));
}

void UAudioManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UAudioManagerSubsystem::PlayButtonHoverSound()
{
	if (ButtonHoverSound)
	{
		UGameplayStatics::SpawnSound2D(this, ButtonHoverSound, 1, 1, .2, nullptr, false, false);
	}
}

void UAudioManagerSubsystem::PlayButtonClickSound()
{
	if (ButtonClickSound)
	{
		UGameplayStatics::SpawnSound2D(this, ButtonClickSound, 1, 1, .2, nullptr, true, false);
	}
}

void UAudioManagerSubsystem::PlayPickupSound(USoundBase* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySound2D(this, Sound);
	}
}

void UAudioManagerSubsystem::PlayMainLoopSound()
{
	if (MainLoopComponent)
	{
		MainLoopComponent->SetPaused(false);
	}
	else
	{
		MainLoopComponent = UGameplayStatics::SpawnSound2D(this, MainLoopSound, 1, 1, 0, nullptr, true, false);
	}
}

void UAudioManagerSubsystem::StopMainLoopSound()
{
	if (MainLoopComponent)
	{
		MainLoopComponent->SetPaused(true);
	}
}

void UAudioManagerSubsystem::PlaySuccessSound()
{
	if (SuccessSound)
	{
		UGameplayStatics::PlaySound2D(this, SuccessSound);
	}
}

void UAudioManagerSubsystem::PlayFailSound()
{
	if (FailSound)
	{
		UGameplayStatics::PlaySound2D(this, FailSound);
	}
}

void UAudioManagerSubsystem::PlayPowerUpStartSound()
{
	if (PowerUpStartSound)
	{
		UGameplayStatics::PlaySound2D(this, PowerUpStartSound);
	}
}

void UAudioManagerSubsystem::PlayPowerUpEndSound()
{
	if (PowerUpEndSound)
	{
		UGameplayStatics::PlaySound2D(this, PowerUpEndSound);
	}
}
