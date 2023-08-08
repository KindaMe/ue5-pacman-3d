#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKey.h"
#include "GhostController.generated.h"

UCLASS()
class PACMAN3D_API AGhostController : public AAIController
{
	GENERATED_BODY()

public:
	AGhostController();
	virtual ~AGhostController() override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void RegisterBlackboardObserver(FName KeyName);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void UnregisterBlackboardObserver(FName KeyName);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnBlackboardValueChanged(FName KeyName);

private:
	EBlackboardNotificationResult OnBlackboardValueChanged_Native(const UBlackboardComponent& BB,
	                                                              FBlackboard::FKey ChangedKeyID);

	// Maps KeyID to DelegateHandle for managing observers
	TMap<FBlackboard::FKey, FDelegateHandle> BlackboardObservers;
};
