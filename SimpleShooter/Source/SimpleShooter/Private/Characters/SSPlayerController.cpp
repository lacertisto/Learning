// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SSPlayerController.h"

void ASSPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	UE_LOG(LogTemp,Warning,TEXT("GameHasEnded of ASSPlayerController has called!"));
	Super::GameHasEnded(EndGameFocus, bIsWinner);
}
