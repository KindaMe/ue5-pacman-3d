// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioManager.generated.h"

UCLASS()
class PACMAN3D_API UAudioManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="Audio|UI")
	void PlayButtonHoverSound();

	UFUNCTION(BlueprintCallable, Category="Audio|UI")
	void PlayButtonClickSound();

	UFUNCTION(BlueprintCallable, Category="Audio|Gameplay")
	void PlayPickupSound(USoundBase* Sound);

	UFUNCTION(BlueprintCallable, Category="Audio|Misc")
	void PlayMainLoopSound();

	UFUNCTION(BlueprintCallable, Category="Audio|Misc")
	void StopMainLoopSound();

	UFUNCTION(BlueprintCallable, Category="Audio|Gameplay")
	void PlaySuccessSound();

	UFUNCTION(BlueprintCallable, Category="Audio|Gameplay")
	void PlayFailSound();

	UFUNCTION(BlueprintCallable, Category="Audio|Gameplay")
	void PlayPowerUpStartSound();

	UFUNCTION(BlueprintCallable, Category="Audio|Gameplay")
	void PlayPowerUpEndSound();

private:
	UPROPERTY()
	USoundBase* ButtonHoverSound;

	UPROPERTY()
	USoundBase* ButtonClickSound;

	UPROPERTY()
	USoundBase* MainLoopSound;

	UPROPERTY()
	USoundBase* SuccessSound;

	UPROPERTY()
	USoundBase* FailSound;

	UPROPERTY()
	USoundBase* PowerUpStartSound;

	UPROPERTY()
	USoundBase* PowerUpEndSound;

private:
	// UPROPERTY()
	// USoundConcurrency* SoundConcurrencyUI;

	UPROPERTY()
	UAudioComponent* MainLoopComponent;
};
