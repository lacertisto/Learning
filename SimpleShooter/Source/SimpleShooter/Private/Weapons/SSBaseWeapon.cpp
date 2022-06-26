// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Characters/SSBaseCharacter.h"
#include "Sound/SoundCue.h"

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
	UGameplayStatics::SpawnSoundAttached(ShotSoundCue,MeshComponent,TEXT("MuzzleFlashSocket"));
	
	FHitResult HitResult;
	FVector ShotDirection;
	if(GunTrace(HitResult,ShotDirection))
	{
		// DrawDebugPoint(GetWorld(),HitResult.Location,20,FColor::Red,true,5.f);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitFlash,HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ImpactSoundCue,HitResult.Location,ShotDirection.Rotation());
		
		AActor* HitActor = HitResult.GetActor();
		if(!HitActor) return;
		FPointDamageEvent DamageEvent(Damage,HitResult,ShotDirection,nullptr);
		AController* OwnerController = GetOwnerController();
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController,this);
	}
}

// Called when the game starts or when spawned
void ASSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ASSBaseWeapon::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if(!OwnerController) return false;
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * ShootRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit,Location,End,ECollisionChannel::ECC_GameTraceChannel1,Params);
}

AController* ASSBaseWeapon::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) return nullptr;
	return OwnerPawn->GetController();
}

// Called every frame
void ASSBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


