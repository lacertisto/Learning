// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SSBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ASSBaseWeapon;

UCLASS()
class SIMPLESHOOTER_API ASSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSBaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin = 1.f, ClampMax = 100.f))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSubclassOf<ASSBaseWeapon> WeaponClass;

	UPROPERTY()
	ASSBaseWeapon* Weapon;
	
private:
	void Strafe(float Scale);
	void Move(float Scale);
	void LookUp(float Scale);
	void LookRight(float X);
	void Shoot();
	
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	
	
};
