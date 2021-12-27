// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"


class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	FOnClipEmptySignature OnClipEmpty;
	
	virtual void StartFire();
	virtual void StopFire();
	void ChangeClip();
	bool CanReload() const;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
	FAmmoData DefaultAmmo{15,10,false};
	
	virtual void BeginPlay() override;

	virtual void MakeShot();
	
	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;
	
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	
	bool GetAimAngle(FHitResult& CameraHitResult);

	void  MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
	
	bool IsAmmoEmpty() const;
	
	bool IsClipEmpty() const;
	
	
	void LogAmmo();

private:

	FAmmoData CurrentAmmo;
};
