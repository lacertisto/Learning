// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEU_WeaponComponent.generated.h"

class ASEU_BaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTEMUP_API USEU_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USEU_WeaponComponent();

	void StartFire();
	void StopFire();
	void SwapWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<ASEU_BaseWeapon>> WeaponClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponArmoryPointName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ASEU_BaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASEU_BaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	void SpawnWeapons();
	void AttachWeaponToSocket(ASEU_BaseWeapon* Weapon, USceneComponent* CharacterMesh, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* AnimMontage);
};
