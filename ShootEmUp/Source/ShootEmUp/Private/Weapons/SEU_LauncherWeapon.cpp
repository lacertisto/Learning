// Pupa&Lupa sftwr. All rights reserved!


#include "Weapons/SEU_LauncherWeapon.h"
#include "SEU_LauncherWeapon.h"

void ASEU_LauncherWeapon::PerformShot()
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

void ASEU_LauncherWeapon::StartFire()
{
}

void ASEU_LauncherWeapon::StopFire()
{
}