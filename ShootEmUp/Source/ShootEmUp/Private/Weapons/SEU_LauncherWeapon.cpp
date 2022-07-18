// Pupa&Lupa sftwr. All rights reserved!


#include "Weapons/SEU_LauncherWeapon.h"
#include "SEU_LauncherWeapon.h"
#include "Weapons/SEU_Projectile.h"

void ASEU_LauncherWeapon::PerformShot()
{
	if (!GetWorld()) return;
	
	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	PerformLineTrace(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ASEU_Projectile* Projectile = GetWorld()->SpawnActorDeferred<ASEU_Projectile>(ProjectileClass, SpawnTransform);

	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->FinishSpawning(SpawnTransform);
	}

}

void ASEU_LauncherWeapon::StartFire()
{
	PerformShot();
}

void ASEU_LauncherWeapon::StopFire()
{
}