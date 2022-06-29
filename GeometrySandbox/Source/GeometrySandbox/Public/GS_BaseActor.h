// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GS_BaseActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,Category="Movement")
    float Amplitude = 50.f;
    
    UPROPERTY(EditAnywhere, Category="Movement")
    float Frequency = 2.f;
    
    UPROPERTY(EditAnywhere, Category="Movement")
    EMovementType MovementType = EMovementType::Static;

	UPROPERTY(EditAnywhere, Category="Design")
	FLinearColor MaterialColor = FLinearColor::Black;
	
	UPROPERTY(EditAnywhere, Category="Design")
	float TimerRate = 3.0f;
};


UCLASS()
class GEOMETRYSANDBOX_API AGS_BaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGS_BaseActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category="GeometryData")
	FGeometryData GeometryData;	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	float WeaponsNum = 4.f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleMovement(const float &DeltaTime);
private:
	FVector InitialLocation;

	void SetColor(const FLinearColor& Color);

	FTimerHandle TimerHandle;

	void OnTimerFired();

	int32 TimerCount;
	const int32 MaxTimerCount = 5;
	
};
