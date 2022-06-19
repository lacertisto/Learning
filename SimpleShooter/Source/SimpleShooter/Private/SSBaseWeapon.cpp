// Fill out your copyright notice in the Description page of Project Settings.


#include "SSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ASSBaseWeapon::ASSBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Gun Mesh");
	MeshComponent->SetupAttachment(Root);
}

void ASSBaseWeapon::Fire()
{
	UE_LOG(LogTemp,Warning,TEXT("Firing a shot!"));
}

// Called when the game starts or when spawned
void ASSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

