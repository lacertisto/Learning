// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Combat")
	float Damage = 25.f;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystemComponent* ProjectileTrail;

	UPROPERTY(EditAnywhere,Category="Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere,Category="Combat")
	USoundBase* HitSound;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, //Source Component 
		AActor* OtherActor, //Hitted Actor that owns other component
		UPrimitiveComponent* OtherComponent, //Component to be hit
		FVector NormalImpulse, //handle for physics system
		const FHitResult& Hit);  //data to write hit events
};
