// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SSBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SIMPLESHOOTER_API ASSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSBaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UCameraComponent* CameraComponent;
	
private:
	void Strafe(float Scale);
	void Move(float Scale);
	void LookUp(float Scale);
	void LookRight(float X);
	
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	
	
};
