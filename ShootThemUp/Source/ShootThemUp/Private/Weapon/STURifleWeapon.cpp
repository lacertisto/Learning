// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "STUUtils.hpp"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


ASTURifleWeapon::ASTURifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}


void ASTURifleWeapon::MakeShot()
{
	// UE_LOG(LogTemp,Display,TEXT("Make shot!"));
	if(!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}
	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}
	FVector Location;
	FRotator Rotation; 
	GetPlayerViewPoint(Location,Rotation);
	
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);


	FVector TraceFXEnd = TraceEnd;
	if(HitResult.bBlockingHit && GetAimAngle(HitResult)) 
	{
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		AActor* Target = HitResult.GetActor();
		TraceFXEnd = HitResult.ImpactPoint;
		
		if (Target != nullptr)
		{
			FPointDamageEvent PointDamageEvent;
			PointDamageEvent.HitInfo = HitResult;
			Target->TakeDamage(DamageAmount,PointDamageEvent,GetController(),this);
		}
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	DecreaseAmmo();
}

void ASTURifleWeapon::StartFire()
{
	InitFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle,this,&ASTURifleWeapon::MakeShot,TimeBetweenShots,true);
	MakeShot();
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetFXActive(false);
}

void ASTURifleWeapon::Zoom(bool bIsEnabled)
{
	const auto Controller = Cast<APlayerController>(GetController());
	if(!Controller || !Controller->PlayerCameraManager) return;

	if(bIsEnabled)
	{
		DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
	}
	
	Controller->PlayerCameraManager->SetFOV(bIsEnabled ? FOVZoomAngle : DefaultCameraFOV);
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

void ASTURifleWeapon::InitFX()
{
	if(!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	if(!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound,WeaponMeshComponent,MuzzleSocketName);
	}
	SetFXActive(true);
}

void ASTURifleWeapon::SetFXActive(bool bIsActive)
{
	if(MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!bIsActive);
		MuzzleFXComponent->SetVisibility(bIsActive,false);
	}

	if(FireAudioComponent)
	{
		FireAudioComponent->SetPaused(!bIsActive);
	}
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),TraceFX, TraceStart);
	if(TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

AController* ASTURifleWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->Controller : nullptr;
	
}