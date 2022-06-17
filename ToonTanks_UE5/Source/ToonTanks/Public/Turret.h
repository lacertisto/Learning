// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	ATurret();

	virtual void Tick(float DeltaSeconds) override;

	virtual void HandleDestruction() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Range")
	float FireRange = 1000.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Rotation")
	float RotationRate = 45.f;
	
	virtual void BeginPlay() override;
	
private:

	bool IsInFireRange();

	ATank* Target;

	FTimerHandle FireTimerTimerHandle;
	float FireRate = 2.f;
	void CheckFireConditions();
	FRotator CurrentRotation = FRotator(0.f);

	bool bAlive = true;
};
