// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATurret::ATurret()
{
}

void ATurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(IsInFireRange())
	{
		RotateTurret(Target->GetActorLocation());
	}
	else
	{
		//make turret rotate in 180 degrees
		//get current rotation
		//continue adding degrees while 180 is not reached
		//invert movement for the same amount
		// CurrentRotation.Yaw += 1 * DeltaSeconds * RotationRate;
		// UE_LOG(LogTemp,Warning,TEXT("Rotation^ %s"),*CurrentRotation.ToString());
		// TurretMesh->AddLocalRotation(CurrentRotation);
	}
	
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
}


void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	GetWorldTimerManager().SetTimer(FireTimerTimerHandle,this,&ATurret::CheckFireConditions,FireRate,true);
}

bool ATurret::IsInFireRange()
{
	if(Target)
	{
		float Distance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());
		if(Distance <= FireRange)
		{
			return true;
		}
		return false;
	}
	return false;
}

void ATurret::CheckFireConditions()
{
	if(IsInFireRange())
	{
		Fire();
	}
}
