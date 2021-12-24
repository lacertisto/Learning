// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int32 Bullets;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta=(EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	bool Infinite;
};

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();
	
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
	
	void ChangeClip();
	
	void LogAmmo();

private:

	FAmmoData CurrentAmmo;
};
