// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ASSAIController::ASSAIController()
{
	
}

void ASSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(LineOfSightTo(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPosition"), UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation());
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}

void ASSAIController::BeginPlay()
{
	Super::BeginPlay();
	if(AIBehaviorTree)
	{
		RunBehaviorTree(AIBehaviorTree);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
	}


}
