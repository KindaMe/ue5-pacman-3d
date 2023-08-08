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

UCLASS(Abstract/*meta = (PrioritizeCategories = "abc def ghi")*/)
class PACMAN3D_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Speed Multiplier */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Speed")
	float SpeedMultiplier;

	/** Dead State */
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	bool bIsDead;

	/** Default Speed */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Speed", meta = (ClampMin = "0"))
	float DefaultSpeed;

	/** Default Static Mesh Material */
	UPROPERTY(EditDefaultsOnly, Category = "Default|Materials")
	TObjectPtr<UMaterialInterface> DefaultStaticMeshMaterial;

	/** Floating Pawn Movement Component */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	/** Camera Component */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UCameraComponent> Camera;

	/** Spring Arm Component */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<USpringArmComponent> SpringArm;

	/** Capsule Collision Component */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UCapsuleComponent> CapsuleCollision;

	/** Static Mesh Component */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** Arrow Component */
	UPROPERTY()
	TObjectPtr<UArrowComponent> Arrow;

public:
	/**  */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPawnIsDead OnPawnIsDead;

	/** Resets Current Speed to default  */
	UFUNCTION(BlueprintCallable, Category = "Default")
	virtual void ResetCurrentSpeedToDefault();

	/** Gets Default Speed */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetDefaultSpeed(float& OutDefaultSpeed) const;

	/** Gets Current Speed */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetCurrentSpeed(float& OutCurrentSpeed) const;

	/** Sets Current Speed */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void SetCurrentSpeed(float NewSpeed);

	/** Gets Speed Multiplier */
	UFUNCTION(BlueprintPure, Category = "Default")
	void GetSpeedMultiplier(float& OutSpeedMultiplier) const;

	/** Sets Speed Multiplier */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void SetSpeedMultiplier(float NewSpeedMultiplier);

	/** Sets Dead State */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void SetIsDead(bool IsDead);

	/** Triggers when IsDead value changes */
	UFUNCTION(BlueprintImplementableEvent, Category = "Default")
	void OnSetIsDead(bool IsDead);

	/** Sets Mesh Material */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void SetMeshMaterial(UMaterialInterface* NewMaterial);

	/** Resets Mesh Material to default */
	UFUNCTION(BlueprintCallable, Category = "Default")
	void ResetMeshMaterialToDefault();
};
