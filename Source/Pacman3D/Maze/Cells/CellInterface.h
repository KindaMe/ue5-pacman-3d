// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CellInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UCellInterface : public UInterface
{
	GENERATED_BODY()
};

class PACMAN3D_API ICellInterface
{
	GENERATED_BODY()

public:
	/** Updates class of the PARENT ChildActorComponent */
	UFUNCTION(BlueprintCallable, Category = "Cell")
	virtual void ChangeCellParentComponentClass(TSubclassOf<class ACell> NewParentClass, bool& bOutSuccess) = 0;
};
