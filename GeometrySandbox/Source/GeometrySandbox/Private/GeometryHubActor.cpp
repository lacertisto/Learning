// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

//initialize new logging category
DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All);

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	//DoActorSpawn1();
	//DoActorSpawn2();
	//DoActorSpawn3(); //initialize new geometry object after game starts
	DoActorSpawn4();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogGeometryHub, Warning, TEXT("Proprty pointer %i, is valid %i"),PropertyActor != nullptr, IsValid(PropertyActor));
	UE_LOG(LogGeometryHub, Error, TEXT("None proprty pointer %i, is valid %i"),NonePropertyActor != nullptr, IsValid(NonePropertyActor));
}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld();
	if(World)
	{
		for (int32 i = 0; i < 10; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator,FVector(0.0f,300.0f * i,300.0f));
			ABaseGeometryActor* Geometry = World -> SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);
 			
			if(Geometry)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
 			
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();
	if(World)
	{
		for (int32 i = 0; i < 10; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator,FVector(0.0f,300.0f * i,700.0f));
			ABaseGeometryActor* Geometry = World -> SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if(Geometry)
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
		}	
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
	UWorld* World = GetWorld(); //get world information as a pointer
	if(World)
	{
		for(const FGeometryPayload Payload: GeometryPayloads)
        {
        	ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform); //create new geometry object from template function, based on payload

			if(Geometry)
        	{
        		Geometry->SetGeometryData(Payload.Data); //sets the object data from payload
				Geometry->OnColorChanged.AddDynamic(this,&AGeometryHubActor::OnColorChanged); // bind for dynamic delegate
				Geometry->OnTimerFinished.AddUObject(this,&AGeometryHubActor::OnTimerFinished); //bind for static delegate
				Geometry->FinishSpawning(Payload.InitialTransform); //destroy the object
        	}
        }		
	}
}

void AGeometryHubActor::DoActorSpawn4()
{
	if(!GetWorld()) return;
	FTransform GeometryTransform = FTransform(FRotator::ZeroRotator,FVector(700.0f,300.0f,700.0f));
	NonePropertyActor = GetWorld() -> SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);	

	GeometryTransform = FTransform(FRotator::ZeroRotator,FVector(700.0f,700.0f,700.0f));
	PropertyActor = GetWorld() -> SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name) //function to assign for delegation
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s Color: %s"), *Name, *Color.ToString())
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor) //function to assign for delegation
{
	if(!Actor) return;
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor); //converts object from one class to another
	if(!Geometry) return;
	UE_LOG(LogGeometryHub, Display, TEXT("Cast successeded, amplitude: %f"), Geometry->GetGeometryData().Amplitude);

	Geometry->Destroy(); //destructor
	//Geometry->SetLifeSpan(2.0f); //another way to destruct the object
}

