// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SIMPLESHOOTER_API ASSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSBaseWeapon();

	void Fire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
