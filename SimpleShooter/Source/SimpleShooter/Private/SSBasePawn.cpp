// Fill out your copyright notice in the Description page of Project Settings.


#include "SSBasePawn.h"

// Sets default values
ASSBasePawn::ASSBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASSBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASSBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

