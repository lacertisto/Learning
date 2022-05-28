// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MovePlatform(float DeltaTime);

	UFUNCTION()
	void RotatePlatform(float DeltaTime);

private:
	
	UPROPERTY(EditAnywhere, Category="Moving Platform")
	FVector PlatformVelocity = FVector(100,0,0);

	UPROPERTY(EditAnywhere, Category="Rotating Platform")
	FRotator PlatformRotation = FRotator(0,0,0);
	
	UPROPERTY(EditAnywhere, Category="Moving Platform")
	float MoveDistance = 100;
	
	FVector StartPosition;

	bool ShouldPlatformReturn(FVector CurrentLocation) const;
};
