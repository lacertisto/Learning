// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

DEFINE_LOG_CATEGORY_STATIC(LogMovingPlatform, All,All);

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = CurrentLocation + PlatformVelocity*DeltaTime;	
	SetActorLocation(CurrentLocation);
	
	float Distance = FVector::Dist(StartPosition, CurrentLocation);
    	if(ShouldPlatformReturn(CurrentLocation))
    	{
    		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
    		StartPosition = StartPosition + MoveDirection * MoveDistance;
    		SetActorLocation(StartPosition);
    		PlatformVelocity = -PlatformVelocity;
    	}
    
    	UE_LOG(LogMovingPlatform, Warning, TEXT("Platform %s overshoot for: %f"),*GetActorNameOrLabel(),Distance - MoveDistance);
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation = CurrentRotation + PlatformRotation * DeltaTime;
	SetActorRotation(CurrentRotation);
}

bool AMovingPlatform::ShouldPlatformReturn(FVector CurrentLocation) const
{
	float Distance = FVector::Dist(StartPosition, CurrentLocation);
	return Distance > MoveDistance;	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	
	RotatePlatform(DeltaTime);
}

