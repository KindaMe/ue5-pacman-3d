#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <GameFramework/FloatingPawnMovement.h>
#include <Camera/CameraComponent.h>
#include <Components/ArrowComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/CapsuleComponent.h"

#include "MyPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPawnIsDead, AMyPawn*, Pawn, bool, bIsDead);

UCLASS(Abstract)
class PACMAN3D_API AMyPawn : public APawn
{
	GENERATED_BODY()

	///////////////////////////////////
	/// Constructor
	///

public:
	AMyPawn();


	///////////////////////////////////
	/// Overrides
	///

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;


	///////////////////////////////////
	/// Movement
	///

public:
	UFUNCTION(BlueprintPure, Category = "Movement")
	void GetDefaultSpeed(float& OutDefaultSpeed) const;

	UFUNCTION(BlueprintPure, Category = "Movement")
	void GetCurrentSpeed(float& OutCurrentSpeed) const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetCurrentSpeed(float NewSpeed);
	UFUNCTION(BlueprintCallable, Category = "Movement")

	virtual void ResetCurrentSpeedToDefault();
	UFUNCTION(BlueprintPure, Category = "Movement")

	void GetSpeedMultiplier(float& OutSpeedMultiplier) const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetSpeedMultiplier(float NewSpeedMultiplier);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default|Movement")
	float SpeedMultiplier;

	UPROPERTY(EditDefaultsOnly, Category = "Default|Movement", meta = (ClampMin = "0"))
	float DefaultSpeed;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;


	///////////////////////////////////
	/// State
	///

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPawnIsDead OnPawnIsDead;

	/** Triggers when IsDead value changes */
	UFUNCTION(BlueprintImplementableEvent, Category = "State")
	void OnSetIsDead(bool IsDead);

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetIsDead(bool IsDead);

private:
	/** Dead State */
	UPROPERTY(EditDefaultsOnly, Category = "Default|State")
	bool bIsDead;


	///////////////////////////////////
	/// Materials
	///

public:
	/** Sets Mesh Material */
	UFUNCTION(BlueprintCallable, Category = "Materials")
	void SetMeshMaterial(UMaterialInterface* NewMaterial);

	/** Resets Mesh Material to default */
	UFUNCTION(BlueprintCallable, Category = "Materials")
	void ResetMeshMaterialToDefault();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default|Materials")
	TObjectPtr<UMaterialInterface> DefaultStaticMeshMaterial;


	///////////////////////////////////
	/// Camera
	///

private:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;


	///////////////////////////////////
	/// Collision
	///

private:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
	TObjectPtr<UCapsuleComponent> CapsuleCollision;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
	TObjectPtr<UStaticMeshComponent> StaticMesh;


	///////////////////////////////////
	/// Other Components
	///

private:
	UPROPERTY()
	TObjectPtr<UArrowComponent> Arrow;
};
