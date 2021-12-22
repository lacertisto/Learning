// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

void ASTURifleWeapon::MakeShot()
{
	if(!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd)) return;

	FVector Location;
	FRotator Rotation; 
	GetPlayerViewPoint(Location,Rotation);
	
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if(HitResult.bBlockingHit) 
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		AActor* Target = HitResult.GetActor();
		GetAimAngle(HitResult);
		if (HitResult.GetActor() != nullptr )
		{
			Target->TakeDamage(DamageAmount,FDamageEvent(),GetPlayerController(),this);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f,0,3.0f);
	}
	
}

void ASTURifleWeapon::StartFire()
{

	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle,this,&ASTURifleWeapon::MakeShot,TimeBetweenShots,true);
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
	
	//const FTransform SocketTransform = WeaponMeshComponent->GetSocketTransform(MuzzleSocketName);
	TraceStart = ViewLocation; // or SocketTransform.GetLocation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(),HalfRad); // or SocketTransform.GetRotation().GetForwardVector();
	// UE_LOG(LogRifleWeapon,Warning,TEXT("%s"), *ShootDirection.ToString());
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}
