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

	void Fire();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASEU_BaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASEU_BaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
};
