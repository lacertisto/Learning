// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_PlayerController.h"

#include "GS_Pawn.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogGSPlayerController, All, All);

void AGS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!InputComponent) return;
	InputComponent->BindAction("SwitchPawn",IE_Pressed,this,&AGS_PlayerController::SwitchPawn);
}

void AGS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGS_Pawn::StaticClass(), Pawns);
}

void AGS_PlayerController::SwitchPawn()
{
	if(Pawns.Num() <= 1) return;

	AGS_Pawn* CurrentPawn = Cast<AGS_Pawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();

	if(!CurrentPawn) return;
	Possess(CurrentPawn);
	UE_LOG(LogGSPlayerController, Warning, TEXT("Pawn Switched!"));
		
}
