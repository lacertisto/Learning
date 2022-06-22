// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Shoot.h"
#include "AIController.h"
#include "Characters/SSBaseCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ASSBaseCharacter* AIPlayer = Cast<ASSBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if(!AIPlayer && OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIPlayer->Shoot();
	
	return EBTNodeResult::Succeeded;
}
