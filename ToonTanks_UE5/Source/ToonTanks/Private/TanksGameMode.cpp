// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"
#include "Tank.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

ATanksGameMode::ATanksGameMode()
{
	DefaultPawnClass = ATank::StaticClass();
}

void ATanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if(Tank->GetTankController())
		{
			Tank->DisableInput(Tank->GetTankController());
			Tank->GetTankController()->bShowMouseCursor = false;
		}
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
	}
}

void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
