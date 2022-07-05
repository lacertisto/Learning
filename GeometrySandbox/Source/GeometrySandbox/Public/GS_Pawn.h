// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GS_Pawn.generated.h"

class UCameraComponent;

UCLASS()
class GEOMETRYSANDBOX_API AGS_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGS_Pawn();

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditAnywhere)
	float Velocity = 300.f;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	FVector VelocityVector = FVector::ZeroVector;

	void MoveForward(float Scale);
	
	void MoveRight(float Scale);
	
};
