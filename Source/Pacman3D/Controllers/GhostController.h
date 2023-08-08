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

	//** Function to register an observer to a blackboard key. */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void RegisterBlackboardObserver(FName KeyName);

	//** Function to unregister an observer from a blackboard key. */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void UnregisterBlackboardObserver(FName KeyName);

protected:
	//** Blueprint implementable function that triggers when the value of a blackboard key changes. */
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnBlackboardValueChanged(FName KeyName);

private:
	//** Function handling blackboard value changes. */
	EBlackboardNotificationResult OnBlackboardValueChanged_Native(const UBlackboardComponent& BB,
	                                                              FBlackboard::FKey ChangedKeyID);

	//** Map that connects blackboard keys to their respective delegate handles. */
	TMap<FBlackboard::FKey, FDelegateHandle> BlackboardObservers;
};
