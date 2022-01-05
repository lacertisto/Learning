// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STUProjectile.h"

#include "Projects.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"


// Sets default values
ASTUProjectile::ASTUProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

// Called when the game starts or when spawned
void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(ProjectileMovementComponent);
	check(CollisionComponent);
	check(WeaponFXComponent);
	
	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;

	CollisionComponent->IgnoreActorWhenMoving(GetOwner(),true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	
	SetLifeSpan(5.0f);
	
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	if(!GetWorld()) return;
	ProjectileMovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),						// World pointer to get world
		DamageAmount,					// Amount of damage
		GetActorLocation(),				// GetActorOwnerLocation
		DamageRadius,					// Radius in which will be applied damage
		UDamageType::StaticClass(),		// Damage type
		{GetOwner()},					// Ignored Actors
		this,							// Pointer to projectile which caused damage
		GetController(),				// Actor which owns tha damage cause
		DoFullDamage					// switch to designate damage applied behavior
		);

	DrawDebugSphere(GetWorld(), GetActorLocation(),DamageRadius,24,FColor::Red,false,5.0f);
	WeaponFXComponent->PlayImpactFX(Hit);
	Destroy();
}

AController* ASTUProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
