// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
//#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree\BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value"); // this just sets the name to something more readable
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetSelectedBlackboardKey();
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("LastKnownPlayerLocation"));
	return EBTNodeResult::Succeeded;
}
