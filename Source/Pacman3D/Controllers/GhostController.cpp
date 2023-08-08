#include "GhostController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

AGhostController::AGhostController()
{
	//
}

AGhostController::~AGhostController()
{
	UBlackboardComponent* BBComp = GetBlackboardComponent();
	if (BBComp)
	{
		for (const auto& Observer : BlackboardObservers)
		{
			BBComp->UnregisterObserver(Observer.Key, Observer.Value);
		}
	}
}

void AGhostController::RegisterBlackboardObserver(FName KeyName)
{
	UBlackboardComponent* BBComp = GetBlackboardComponent();
	if (BBComp)
	{
		FBlackboard::FKey KeyID = BBComp->GetKeyID(KeyName);
		BlackboardObservers.Add(KeyID, BBComp->RegisterObserver(KeyID, this,
		                                                        FOnBlackboardChangeNotification::CreateUObject(
			                                                        this,
			                                                        &AGhostController::OnBlackboardValueChanged_Native)));
	}
}

void AGhostController::UnregisterBlackboardObserver(FName KeyName)
{
	UBlackboardComponent* BBComp = GetBlackboardComponent();
	if (BBComp)
	{
		FBlackboard::FKey KeyID = BBComp->GetKeyID(KeyName);
		if (BlackboardObservers.Contains(KeyID))
		{
			BBComp->UnregisterObserver(KeyID, BlackboardObservers[KeyID]);
			BlackboardObservers.Remove(KeyID);
		}
	}
}

EBlackboardNotificationResult AGhostController::OnBlackboardValueChanged_Native(
	const UBlackboardComponent& BB, FBlackboard::FKey ChangedKeyID)
{
	FName KeyName = BB.GetKeyName(ChangedKeyID);
	OnBlackboardValueChanged(KeyName);

	return EBlackboardNotificationResult::ContinueObserving;
}
