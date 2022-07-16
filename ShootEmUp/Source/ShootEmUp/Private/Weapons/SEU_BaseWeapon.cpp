// Pupa&Lupa sftwr. All rights reserved!

#include "Weapons/SEU_BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Characters/SEU_BaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
ASEU_BaseWeapon::ASEU_BaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	SetRootComponent(WeaponMeshComponent);
}

// Called when the game starts or when spawned
void ASEU_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMeshComponent)
}

void ASEU_BaseWeapon::PerformShot()
{
	
}

void ASEU_BaseWeapon::StartFire()
{
	
}

void ASEU_BaseWeapon::StopFire()
{
	
}

APlayerController* ASEU_BaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASEU_BaseWeapon::GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const
{
	const APlayerController* Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(OutViewLocation, OutViewRotation);
	return true;
}

FVector ASEU_BaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool ASEU_BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = ViewLocation + ShootDirection * TraceMaxDistance;
	return true;
}

void ASEU_BaseWeapon::PerformLineTrace(FHitResult& OutHitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(OutHitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, QueryParams);
}

float ASEU_BaseWeapon::GetShotAngle(const FHitResult& HitResult, const FVector& TraceEnd) const
{
	const FVector FinalTraceEnd = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector MuzzleHitDirection = (FinalTraceEnd - GetMuzzleWorldLocation()).GetSafeNormal();
		
	return FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(
			WeaponMeshComponent->GetSocketQuaternion(MuzzleSocketName).GetForwardVector(), MuzzleHitDirection)));
}

void ASEU_BaseWeapon::InflictDamage(const FHitResult& HitResult)
{
	const auto Victim = HitResult.GetActor();
	if (Victim)
	{
		Victim->TakeDamage(Damage, FDamageEvent{}, GetPlayerController(), GetOwner());
	}
}