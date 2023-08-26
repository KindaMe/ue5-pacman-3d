// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellInterface.h"
#include "CellType.h"
#include "Cell.generated.h"

UCLASS(Abstract)
class PACMAN3D_API ACell : public AActor, public ICellInterface
{
	GENERATED_BODY()


	///////////////////////////////////
	/// Constructor
	///

public:
	ACell();


	///////////////////////////////////
	/// Overrides
	///

protected:
	virtual void BeginPlay() override;


	///////////////////////////////////
	/// Collision
	///

private:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"),
		Category = "Collision")
	TObjectPtr<UStaticMeshComponent> StaticMesh;


	///////////////////////////////////
	/// Cell Info
	///

public:
	/** Returns CellType of a cell */
	UFUNCTION(BlueprintPure, Category="Info")
	void GetCellType(ECellType& OutCellType) const;

	/** Returns DisplayName of a cell */
	UFUNCTION(BlueprintPure, Category="Info")
	void GetDisplayName(FName& OutDisplayName) const;

protected:
	/** Cell Category mainly used in maze creator */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Default|Info")
	ECellType CellType;

	/** Cell Display Name mainly used in maze creator */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Default|Info")
	FName DisplayName;


	///////////////////////////////////
	/// Child Actor Component
	///

public:
	/** Gets child actor stored in ChildActorComponent */
	UFUNCTION(BlueprintPure, Category="Child Actor")
	void GetCellChildActor(AActor*& OutChildActor) const;

private:
	/** ChildActorComponent meant to hold ghosts, pickups etc */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"),
		Category = "Child Actor")
	TObjectPtr<UChildActorComponent> ChildActorComponent;


	///////////////////////////////////
	/// PARENT Child Actor Component
	///

public:
	/** Updates class of the PARENT ChildActorComponent */
	virtual void ChangeCellParentComponentClass(TSubclassOf<ACell> NewParentClass, bool& bOutSuccess) override;
};
