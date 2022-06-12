// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "HealthComponent.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	RootComponent = CapsuleComponent;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(CapsuleComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
}

void ABasePawn::HandleDestruction()
{
	//TODO: Visual/sound effects handle
	
}

void ABasePawn::RotateTurret(FVector TargetLocation)
{
	FVector ToTarget = TargetLocation - TurretMesh->GetComponentLocation();
	FRotator Rotation = FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
	TurretMesh->SetWorldRotation(Rotation);
}

void ABasePawn::Fire()
{
	// DrawDebugSphere(GetWorld(),ProjectileSpawnPoint->GetComponentLocation(),6,12,FColor::Red,false,5.f);
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPoint->GetComponentLocation(),ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}
