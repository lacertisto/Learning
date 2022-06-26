// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "AI/SSAIController.h"
#include "Characters/SSPlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	
	if(PlayerController != nullptr)
	{
		EndGame(false);
	}

	for(auto Controller : TActorRange<ASSAIController>(GetWorld()))
	{
		if(!Controller->IsDead()) return;
	}
	EndGame(true);
	
}

void AKillEmAllGameMode::EndGame(bool IsPlayerWinner)
{
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool IsWinner = Controller->IsPlayerController() == IsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(),IsWinner);
	}
}
