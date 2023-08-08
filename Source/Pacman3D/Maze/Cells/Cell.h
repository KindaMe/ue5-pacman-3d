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

public:
	ACell();

protected:
	virtual void BeginPlay() override;

private:
	/**  */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** ChildActorComponent meant to hold ghosts, pickups etc */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Default")
	TObjectPtr<UChildActorComponent> ChildActorComponent;

protected:
	/** Cell Category mainly used in maze creator */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Default")
	ECellType CellType;

	/** Cell Display Name mainly used in maze creator */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Default")
	FName DisplayName;

public:
	/** Gets child actor stored in ChildActorComponent */
	UFUNCTION(BlueprintPure, Category="Default")
	void GetCellChildActor(AActor*& OutChildActor) const;

	/** Updates class of the PARENT ChildActorComponent */
	virtual void ChangeCellParentComponentClass(TSubclassOf<ACell> NewParentClass, bool& bOutSuccess) override;

	/** Returns CellType of a cell */
	UFUNCTION(BlueprintPure, Category="Default")
	void GetCellType(ECellType& OutCellType) const;

	/** Returns DisplayName of a cell */
	UFUNCTION(BlueprintPure, Category="Default")
	void GetDisplayName(FName& OutDisplayName) const;
};
