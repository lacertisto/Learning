#include "SEU_WeaponComponent.h"
// Pupa&Lupa sftwr. All rights reserved!


#include "Components/SEU_WeaponComponent.h"
#include "Weapons/SEU_BaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USEU_WeaponComponent::USEU_WeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void USEU_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}

void USEU_WeaponComponent::SpawnWeapon()
{
	if (!GetWorld())	return;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)	return;
	CurrentWeapon = GetWorld()->SpawnActor<ASEU_BaseWeapon>(WeaponClass);
	if (!CurrentWeapon)	return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}

void USEU_WeaponComponent::Fire()
{
	if (!CurrentWeapon)	return;
	CurrentWeapon->Fire();
}
