// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;
private:

};
