// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UHealthComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	virtual void HandleDestruction();

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category="Health")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere,Category="Combat")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere,Category="Combat")
	USoundBase* DeathSound;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;
	
	void RotateTurret(FVector TargetLocation);

	void Fire();
private:

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
};
