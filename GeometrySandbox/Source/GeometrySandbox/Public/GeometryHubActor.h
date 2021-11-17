// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload //struct for generating geometry objects
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass; //class for which the object will be derived

	UPROPERTY(EditAnywhere)
	FGeometryData Data; //actual data

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform; //initial transfrom info (position in the world, rotation and etc)
};

UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor //base class derived from aactor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor(); //constructor

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseGeometryActor> GeometryClass; //sets the object class

	UPROPERTY(EditAnywhere)
		TArray<FGeometryPayload> GeometryPayloads; //array for storing the info about objects to be spawned
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	ABaseGeometryActor* NonePropertyActor;

	UPROPERTY()
	ABaseGeometryActor* PropertyActor;
	
	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();
	void DoActorSpawn4();

	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);

	void OnTimerFinished(AActor* Actor);
};
