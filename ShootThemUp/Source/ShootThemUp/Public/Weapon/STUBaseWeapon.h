// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"


class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

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
	bool IsFiring() const;

	FWeaponUIData GetUIData() const {return UIData;}
	FAmmoData GetCurrentAmmoData() const {return CurrentAmmo;}

	bool TryToAddAmmo(int32 ClipsAmount);
	bool IsAmmoEmpty() const;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
	FAmmoData DefaultAmmo{15,10,false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="VFX")
	UNiagaraSystem* MuzzleFX;
	
	bool FireInProgress = false;
	
	virtual void BeginPlay() override;

	virtual void MakeShot();
	
	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;
	
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	
	bool GetAimAngle(FHitResult& CameraHitResult);

	void  MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
	
	bool IsClipEmpty() const;

	bool IsAmmoFull() const;

	void LogAmmo();

	UNiagaraComponent* SpawnMuzzleFX();
	
private:

	FAmmoData CurrentAmmo;
};
