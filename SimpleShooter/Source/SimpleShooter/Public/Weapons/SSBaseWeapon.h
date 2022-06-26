// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;
class USoundCue;

UCLASS()
class SIMPLESHOOTER_API ASSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSBaseWeapon();

	void Fire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitFlash;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USoundCue* ShotSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundCue* ImpactSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 15.f;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
