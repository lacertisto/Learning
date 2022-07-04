// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GS_BaseActor.h"
#include "GameFramework/Actor.h"
#include "GeometryHubActor.generated.h"

class AGS_BaseActor;

USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGS_BaseActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
};


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
	TSubclassOf<AGS_BaseActor> GeometryClass; //filtered class types to choose

	UPROPERTY(EditAnywhere)
	AGS_BaseActor* GeometryObject; //non-filtered types to choose

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void DoActorSpawn1(UWorld* World);
	void DoActorSpawn2(UWorld* World);
	void DoActorSpawn3(UWorld* World);

	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);

	void OnTimerFinished(AActor* Actor);

};
