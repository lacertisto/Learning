// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this,HUDClass);
	if(HUD)
	{
		HUD->AddToViewport();
	}
}

void ASSPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUD->RemoveFromViewport();
	if(!bIsWinner)
	{
		UUserWidget* LoseScreen = CreateWidget(this,LoseScreenClass);
		if(!LoseScreen) return;
		LoseScreen->AddToViewport();
	}
	else
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if(!WinScreen) return;
		WinScreen->AddToViewport();
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);
}
