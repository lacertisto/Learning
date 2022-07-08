// Pupa&Lupa sftwr. All rights reserved!


#include "Weapons/SEU_BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ASEU_BaseWeapon::ASEU_BaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	SetRootComponent(WeaponMeshComponent);
}

// Called when the game starts or when spawned
void ASEU_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
