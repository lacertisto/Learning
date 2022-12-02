// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Critter.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class CARACAL_API ACritter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACritter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USphereComponent> SphereComponent = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//FORCEINLINE is equal to inline keyword
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetMeshComponent() {return MeshComponent;}
	FORCEINLINE void SetMeshComponent(TObjectPtr<UStaticMeshComponent> Mesh) {MeshComponent = Mesh;}
	FORCEINLINE TObjectPtr<USphereComponent> GetSphereComponent() {return SphereComponent;}
	FORCEINLINE void SetSphereComponent(TObjectPtr<USphereComponent> Sphere) {SphereComponent = Sphere;}

};
