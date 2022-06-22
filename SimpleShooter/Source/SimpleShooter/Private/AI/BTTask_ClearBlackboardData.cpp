// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ClearBlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardData::UBTTask_ClearBlackboardData()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardData::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
