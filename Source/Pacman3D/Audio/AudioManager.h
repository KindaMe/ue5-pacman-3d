// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioManager.generated.h"

UCLASS()
class PACMAN3D_API UAudioManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	///////////////////////////////////
	/// Overrides
	///
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	///////////////////////////////////
	/// Main Loop Audio Component
	///
	
private:
	UPROPERTY()
	UAudioComponent* MainLoopComponent;

	///////////////////////////////////
	/// Sound Triggers
	///
	
public:
	UFUNCTION(BlueprintCallable, Category="UI")
	void PlayButtonHoverSound();

	UFUNCTION(BlueprintCallable, Category="UI")
	void PlayButtonClickSound();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void PlayPickupSound(USoundBase* Sound);

	UFUNCTION(BlueprintCallable, Category="Misc")
	void PlayMainLoopSound();

	UFUNCTION(BlueprintCallable, Category="Misc")
	void StopMainLoopSound();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void PlaySuccessSound();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void PlayFailSound();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void PlayPowerUpStartSound();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void PlayPowerUpEndSound();

	///////////////////////////////////
	/// Cues
	///
	
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


	///////////////////////////////////
	/// Sound Concurrency
	///
	
private:
	// UPROPERTY()
	// USoundConcurrency* SoundConcurrencyUI;
};
