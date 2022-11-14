// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class CARACAL_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

	//Location when the BeginPlay() is called
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Actor | Location")
	FVector InitialLocation = FVector(FMath::FRand());

	//Location of the actor when dragged in from the editor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Actor | Location")
	FVector PlacedLocation = FVector::ZeroVector;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Actor | Location")
	FVector WorldOrigin = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor | Location")
	FVector InitialDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor | Location")
	bool bShouldFloat = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Actor | Location")
	bool bInitializeFloaterLocation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor | Sine")
	float SineAmplitude = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor | Sine")
	float SinePeriod = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor | Sine")
	float SinePhaseShift = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor | Sine")
	float SineVerticalShift = 0.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	float RunningTime = 0.f;

	float BaseZLocation = 0.f;

};
