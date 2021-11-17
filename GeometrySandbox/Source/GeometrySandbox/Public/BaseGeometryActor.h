// Fill out your copyright notice in the Description page of Project Settings.

#pragma once //include file only once 

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

class UStaticMeshComponent;

//delegates declaration (needs the class and objects it will take)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOncolorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);


UENUM(BlueprintType) //variable that could be used for blueprints 
enum class EMovementType : uint8 //movement type class for objects
{
	Sin,
	Static
};

USTRUCT(BlueprintType) //variable that could be used for blueprints
struct FGeometryData //default values of a geometry object that will be spawned
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Movement")
    float Amplitude{50.0f};
    UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category= "Movement")
    float Frequency{2.0f};
    UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category= "Movement")
    EMovementType MoveType = EMovementType::Static;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category= "Design")
	FLinearColor Color = FLinearColor::Black;
	UPROPERTY(EditAnywhere, Category= "Design")
	float TimerRate = 3.0f;	
};

UCLASS() //defines an unreal class
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh; //mesh that will be used as 

	void SetGeometryData(const FGeometryData& Data) //setter
	{
		GeometryData = Data;	
	}

	UFUNCTION(BlueprintCallable) //Multicast Delegates only. Property should be exposed for calling in Blueprint code.
	FGeometryData GetGeometryData() const {return GeometryData;}

	UPROPERTY(BlueprintAssignable) //Usable with Multicast Delegates only. Exposes the property for assigning in Blueprints.
	FOncolorChanged OnColorChanged;
	
	FOnTimerFinished OnTimerFinished; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Geometry Data")
	FGeometryData GeometryData;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum{ 4 };
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum{ 7 };
	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health{ 34 };
	UPROPERTY(EditAnywhere, Category = "Health")
	bool bIsDead{ false };
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool bHasWeapon{ true };

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector InitialLocation;
	FTimerHandle TimerHandle;

	const int32 MaxTimerCount{5};
	int32 TimerCount{0};
	
	void PrintTypes();
	void PrintStringTypes();
	void PrintTransform();
	void HandleMovement();
	void SetColor(const FLinearColor& Color);
	void OnTimerFired();
};
