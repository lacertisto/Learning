// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "GS_BaseActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHubActor, All, All);

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

	UWorld* World = GetWorld();
	if(World)
	{
		// DoActorSpawn1(World);
		// DoActorSpawn2(World);
		DoActorSpawn3(World);
	}
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryHubActor::DoActorSpawn1(UWorld* World)
{
	for(int32 i = 0; i < 10; i++)
    {
    	const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator,FVector(0.f,300.f * i,300.f));
        AGS_BaseActor* GeometryActor = World->SpawnActor<AGS_BaseActor>(GeometryClass, GeometryTransform);
    	if(GeometryActor)
    	{
    		FGeometryData Data;
            Data.MovementType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
            GeometryActor->SetGeometryData(Data);	
    	}
    }
}

void AGeometryHubActor::DoActorSpawn2(UWorld* World)
{
	for(int32 i = 0; i < 10; i++)
    {
        const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator,FVector(0.f,300.f * i,700.f));
        AGS_BaseActor* GeometryActor = World->SpawnActorDeferred<AGS_BaseActor>(GeometryClass, GeometryTransform);
        if(GeometryActor)
        {
            FGeometryData Data;
            Data.MovementType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
    		Data.MaterialColor = FColor::MakeRandomColor();
            GeometryActor->SetGeometryData(Data);
            GeometryActor->FinishSpawning(GeometryTransform);
        }
    }
}

void AGeometryHubActor::DoActorSpawn3(UWorld* World)
{
	for(FGeometryPayload Actor : GeometryPayloads)
	{
	    AGS_BaseActor* GeometryActor = World->SpawnActorDeferred<AGS_BaseActor>(Actor.GeometryClass, Actor.InitialTransform);
	    if(GeometryActor)
	    {
    		GeometryActor->SetGeometryData(Actor.Data);
	    	GeometryActor->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
	    	GeometryActor->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
    		GeometryActor->FinishSpawning(Actor.InitialTransform);
	    }
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHubActor, Warning, TEXT("Actor Color: %s, Actor Name: %s"), *Color.ToString(),*Name);
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if(!Actor) return;
	UE_LOG(LogGeometryHubActor, Error, TEXT("Timer finished for actor: %s"), *Actor->GetName());
	//because here occures upcast (casting to parent class), we want to do downcast

	AGS_BaseActor* GeometryActor = Cast<AGS_BaseActor>(Actor);
	if(!GeometryActor) return;

	UE_LOG(LogGeometryHubActor, Display, TEXT("Cast Successfull, Amplitude of actor is: %s"), GeometryActor->GetGeometryData().Amplitude);

	// GeometryActor->Destroy(); //destroying actor
	// GeometryActor->SetLifeSpan(2.f); //setting lifespan
	
}


