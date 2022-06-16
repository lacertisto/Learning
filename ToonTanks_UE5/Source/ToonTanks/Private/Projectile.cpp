// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
	SetRootComponent(ProjectileMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->MaxSpeed = 1300.f;
	ProjectileMovement->InitialSpeed = 1300.f;

	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>("Projectile Trail");
	ProjectileTrail->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),LaunchSound,GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent
	, FVector NormalImpulse, const FHitResult& Hit)
{
	auto ProjectileOwner = GetOwner();
	if(!ProjectileOwner) return;
	auto MyOwner = ProjectileOwner->GetInstigatorController();
	if(!MyOwner)
	{
		Destroy();
		return;
	}
	
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwner,this,UDamageType::StaticClass());
		if(HitParticles)
		{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticles,GetActorLocation());
		}
		if(HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),HitSound,GetActorLocation());
		}
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	Destroy();
}

