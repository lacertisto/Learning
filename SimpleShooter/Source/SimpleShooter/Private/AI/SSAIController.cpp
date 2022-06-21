// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSAIController.h"

#include "Kismet/GameplayStatics.h"

ASSAIController::ASSAIController()
{
	
}

void ASSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(LineOfSightTo(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		SetFocus(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		MoveToActor(UGameplayStatics::GetPlayerPawn(GetWorld(),0),200);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}

void ASSAIController::BeginPlay()
{
	Super::BeginPlay();



}
