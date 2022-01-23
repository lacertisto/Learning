// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMeshComponent);
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMeshComponent);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count cannot be less or equal to zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count cannot be less or equal to zero"));
	CurrentAmmo = DefaultAmmo;
	
}

void ASTUBaseWeapon::MakeShot()
{

}

void ASTUBaseWeapon::StartFire()
{
	FireInProgress = true;	
}

void ASTUBaseWeapon::StopFire()
{
	FireInProgress = false;
}
	
bool ASTUBaseWeapon::IsFiring() const
{
	return FireInProgress;
}

bool ASTUBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if(CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

	if(IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if(CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if(DefaultAmmo.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;;
		}
	}
	else
	{
		CurrentAmmo.Clips = DefaultAmmo.Clips;
	}
	
	return true;
}


APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{

	const auto STUCharacter = Cast<ACharacter>(GetOwner());
	if(!STUCharacter) return false;
	
	if(STUCharacter->IsPlayerControlled())
	{
		const auto Controller = GetPlayerController();
		if(!Controller) return false;
	
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMeshComponent->GetSocketRotation(MuzzleSocketName);
	}
	
return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
 return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);	
}


bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
	
	//const FTransform SocketTransform = WeaponMeshComponent->GetSocketTransform(MuzzleSocketName);
	TraceStart = ViewLocation; // or SocketTransform.GetLocation();
	const FVector ShootDirection = ViewRotation.Vector(); // or SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void  ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

bool ASTUBaseWeapon::GetAimAngle(FHitResult& CameraHitResult)
{
	const FTransform SocketTransform = WeaponMeshComponent->GetSocketTransform(MuzzleSocketName);
	const FVector ActualTraceEnd = CameraHitResult.bBlockingHit ? CameraHitResult.ImpactPoint : CameraHitResult.TraceEnd;
	const FVector HitDirectionFromMuzzle = (ActualTraceEnd - SocketTransform.GetLocation()).GetSafeNormal();
	const float Degrees = FMath::RadiansToDegrees(
			FMath::Acos(
				FVector::DotProduct(SocketTransform.GetRotation().GetForwardVector(), HitDirectionFromMuzzle)));
     
	//UE_LOG(LogBaseWeapon, Display, TEXT("Shooting angle: %.0f"), Degrees);
	if(Degrees > 90.0f)
	{
	//	UE_LOG(LogBaseWeapon, Error, TEXT("Attempted to shoot backwards!"));
		return false;
	}
	return true;
}

void ASTUBaseWeapon::DecreaseAmmo()
{
	if(CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon,Warning,TEXT("No more bullets"));
		return;
	}
	CurrentAmmo.Bullets --;
	// LogAmmo();

	if(IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}

bool ASTUBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool ASTUBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips &&
		CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void ASTUBaseWeapon::ChangeClip()
{
	if(!CurrentAmmo.Infinite)
	{
		if(CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	// UE_LOG(LogBaseWeapon,Display,TEXT("---------------------Changed Clip--------------------"));
}

bool ASTUBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}


void ASTUBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo" + FString::FromInt(CurrentAmmo.Bullets) + "/";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo)
}

UNiagaraComponent* ASTUBaseWeapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,	//
		WeaponMeshComponent,										//
		MuzzleSocketName,											//
		FVector::ZeroVector,										//
		FRotator::ZeroRotator,										//
		EAttachLocation::SnapToTarget,								//
		true);
}
