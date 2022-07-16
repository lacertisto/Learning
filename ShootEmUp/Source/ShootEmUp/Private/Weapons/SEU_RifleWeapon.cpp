// Pupa&Lupa sftwr. All rights reserved!


#include "Weapons/SEU_RifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ASEU_RifleWeapon::PerformShot()
{
	if (!GetWorld())
		return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
		return;

	FHitResult HitResult;
	PerformLineTrace(HitResult, TraceStart, TraceEnd);

	if (GetShotAngle(HitResult, TraceEnd) < 90.f && HitResult.bBlockingHit)
	{
		InflictDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 5.f, 0, 3.f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 12.f, 24, FColor::Red, false, 5.f, 0, 3.f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 5.f, 0, 3.f);
	}
}

void ASEU_RifleWeapon::StartFire()
{
	PerformShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASEU_RifleWeapon::PerformShot, FireRate, true);
}

void ASEU_RifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

bool ASEU_RifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
		return false;

	TraceStart = ViewLocation;
	const auto HalfRadius = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRadius);
	TraceEnd = ViewLocation + ShootDirection * TraceMaxDistance;
	return true;
}