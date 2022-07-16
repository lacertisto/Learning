// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Weapons/SEU_BaseWeapon.h"
#include "SEU_LauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API ASEU_LauncherWeapon : public ASEU_BaseWeapon
{
	GENERATED_BODY()
	
public:

	virtual void StartFire() override;

	virtual void StopFire() override;

protected:

	virtual void PerformShot() override;
};
