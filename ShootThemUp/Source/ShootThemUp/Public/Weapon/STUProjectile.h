// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUProjectile();

	void SetShotDirection(const FVector& Direction){ShotDirection = Direction;}

protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly,Category="Weapon")
		UProjectileMovementComponent* ProjectileMovementComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector ShotDirection;
};
