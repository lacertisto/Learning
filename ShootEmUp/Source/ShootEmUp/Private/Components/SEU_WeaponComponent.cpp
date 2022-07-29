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

	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USEU_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for(ASEU_BaseWeapon* Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void USEU_WeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Character) return;

	for(TSubclassOf<ASEU_BaseWeapon> WeaponClass : WeaponClasses)
	{
		ASEU_BaseWeapon* Weapon = GetWorld()->SpawnActor<ASEU_BaseWeapon>(WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(Character);
		Weapons.Emplace(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmoryPointName);
	}
	

}

void USEU_WeaponComponent::AttachWeaponToSocket(ASEU_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USEU_WeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Character)
		return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmoryPointName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponAttachPointName);
	PlayAnimMontage(EquipAnimMontage);
}

void USEU_WeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	Character->PlayAnimMontage(AnimMontage);
}

void USEU_WeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void USEU_WeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USEU_WeaponComponent::SwapWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
