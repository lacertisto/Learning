// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometryHubActor.generated.h"

class AGS_BaseActor;

UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGS_BaseActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	AGS_BaseActor* GeometryObject;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
