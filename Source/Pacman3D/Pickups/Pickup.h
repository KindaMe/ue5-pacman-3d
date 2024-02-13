// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/CapsuleComponent.h>

#include "Pickup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCollected, APickup*, Pickup, int, Score);

UCLASS(Abstract)
class PACMAN3D_API APickup : public AActor
{
	GENERATED_BODY()


	///////////////////////////////////
	/// Constructor
	///

public:
	APickup();


	///////////////////////////////////
	/// Overrides
	///

protected:
	virtual void BeginPlay() override;


	///////////////////////////////////
	/// Collision
	///

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	/**  */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
	TObjectPtr<UCapsuleComponent> CapsuleCollision;

	/**  */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
	TObjectPtr<UStaticMeshComponent> StaticMesh;


	///////////////////////////////////
	/// Sound
	///

private:
	UPROPERTY(EditDefaultsOnly, Category="Default|Sound")
	USoundBase* PickupSound;


	///////////////////////////////////
	/// Score
	///

public:
	UFUNCTION(BlueprintPure, Category="Score")
	void GetScore(int32& OutScore) const;

private:
	/** Score value assigned to pickup */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Score", meta = (ClampMin = "0"))
	int32 Score;


	///////////////////////////////////
	/// Effects
	///

protected:
	/** Call any PickupInterface Effects you want here. If GameMode is valid then it implements PickupInterface. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Effects")
	void ApplyPickupEffects(AGameModeBase* GameMode);

	///////////////////////////////////
	/// Delegates
	///

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCollected OnCollected;
};
