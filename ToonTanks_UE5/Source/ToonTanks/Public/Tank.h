// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void HandleDestruction() override;

	APlayerController* GetTankController() const {return PlayerController;}
	
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Movement")
	float Speed = 100.f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Rotation")
	float TurnRate = 45.f;
	
	virtual void BeginPlay() override;
	
private:

	void Move(float Move);

	void Rotate(float Rotation);

	APlayerController* PlayerController;
	
};
