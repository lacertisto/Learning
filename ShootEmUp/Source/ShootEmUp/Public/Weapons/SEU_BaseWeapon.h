// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEU_BaseWeapon.generated.h"

class USkeletalMeshComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = "Damage")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float FireRate = 0.1f;

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

private:

	
};
