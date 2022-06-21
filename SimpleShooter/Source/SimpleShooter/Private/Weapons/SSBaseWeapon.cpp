// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Characters/SSBaseCharacter.h"


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
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent,TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) return;
	AController* OwnerController = OwnerPawn->GetController();
	if(!OwnerController) return;
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * ShootRange;

	FHitResult HitResult;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult,Location,End,ECollisionChannel::ECC_GameTraceChannel1);
	if(bSuccess)
	{
		// DrawDebugPoint(GetWorld(),HitResult.Location,20,FColor::Red,true,5.f);
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitFlash,HitResult.Location, ShotDirection.Rotation());
		
		AActor* HitActor = HitResult.GetActor();
		if(!HitActor) return;
		FPointDamageEvent DamageEvent(Damage,HitResult,ShotDirection,nullptr);
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController,this);
	}
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


