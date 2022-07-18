// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Weapons/SEU_BaseWeapon.h"
#include "SEU_LauncherWeapon.generated.h"

class ASEU_Projectile;

UCLASS()
class SHOOTEMUP_API ASEU_LauncherWeapon : public ASEU_BaseWeapon
{
	GENERATED_BODY()
	
public:

	virtual void StartFire() override;

	virtual void StopFire() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASEU_Projectile> ProjectileClass;

	virtual void PerformShot() override;
};
