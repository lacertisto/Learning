// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_PlayerLocationIfSeen.h"

#include "AI/SSAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AController* AIPlayer = OwnerComp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(!AIPlayer || !PlayerPawn) return;
	if(AIPlayer->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());	
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
	
}
