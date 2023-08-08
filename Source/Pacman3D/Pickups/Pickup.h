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

public:
	APickup();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	/**  */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UCapsuleComponent> CapsuleCollision;

	/**  */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/**  */
	UPROPERTY(EditDefaultsOnly, Category="Default")
	USoundBase* PickupSound;

	/**  */
	UPROPERTY(EditDefaultsOnly, Category = "Default", meta = (ClampMin = "0"))
	int32 Score;

protected:
	/** Call any PickupInterface Effects you want here. If GameMode is valid then it implements PickupInterface. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Default")
	void ApplyPickupEffects(AGameModeBase* GameMode);

	/**  */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	/**  */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCollected OnCollected;

	/** Returns score value of a pickup */
	UFUNCTION(BlueprintPure, Category="Default")
	void GetScore(int32& OutScore) const;
};
