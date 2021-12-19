// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Viewports.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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
}

void ASTUBaseWeapon::MakeShot()
{
	if(!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if(HitResult.bBlockingHit && HitResult.GetActor() != nullptr)
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		AActor* Target = HitResult.GetActor();
		UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s, Actor: %s"), *HitResult.BoneName.ToString(), *Target->GetName());
		Target->TakeDamage(DamageAmount,FDamageEvent(),GetPlayerController(),this);
		
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation() , TraceEnd, FColor::Red, false, 3.0f,0,3.0f);
	}
	
}

void ASTUBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon,Display,TEXT("Fire!"));

	MakeShot();
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if(!Controller) return false;
	
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
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
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}