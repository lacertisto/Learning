// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEU_BaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo", meta=(EditCondition = "!bHasInfiniteAmmo"))
	int32 ClipsAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	bool bHasInfiniteAmmo;
};

UCLASS()
class SHOOTEMUP_API ASEU_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASEU_BaseWeapon();

	virtual void StartFire();

	virtual void StopFire();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = "Weapon | Damage")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Damage")
	float Damage = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Damage")
	float FireRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Ammo")
	FAmmoData DefaultAmmo{30, 5, false};

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PerformShot();
	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void PerformLineTrace(FHitResult& OutHitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
	float GetShotAngle(const FHitResult& HitResult, const FVector& TraceEnd) const;
	void InflictDamage(const FHitResult& HitResult);
	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	void Reload();
	void LogAmmo();

	private:
	FAmmoData CurrentAmmo;
};
