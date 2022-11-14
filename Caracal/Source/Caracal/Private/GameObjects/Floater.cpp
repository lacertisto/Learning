// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObjects/Floater.h"	

DEFINE_LOG_CATEGORY_STATIC(LogFloater, All, All);

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);

}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	PlacedLocation = GetActorLocation();


	if(bInitializeFloaterLocation)
	{
		SetActorLocation(InitialLocation);
	}
	if(StaticMesh->IsSimulatingPhysics())
	{
		FVector InitialForce = FVector(0.f, 20000.f, 0.f);
		StaticMesh->AddForce(InitialForce);
	}

	BaseZLocation = PlacedLocation.Z;
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bShouldFloat)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z = BaseZLocation + (SineAmplitude * FMath::Sin(SinePeriod * RunningTime - SinePhaseShift) + SineVerticalShift);

		SetActorLocation(NewLocation);
		FHitResult HitResult;
		AddActorLocalOffset(InitialDirection,false, &HitResult);
		RunningTime += DeltaTime;

	}
}

