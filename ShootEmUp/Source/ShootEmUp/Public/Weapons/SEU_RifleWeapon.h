// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Weapons/SEU_BaseWeapon.h"
#include "SEU_RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API ASEU_RifleWeapon : public ASEU_BaseWeapon
{
	GENERATED_BODY()

public:

	virtual void StartFire() override;

	virtual void StopFire() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float BulletSpread = 1.5f;

	virtual void PerformShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:

	FTimerHandle ShotTimerHandle;
};
