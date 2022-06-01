// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabberComponent::Grab()
{
	FVector Start = GetComponentLocation();
    	FVector End = Start + GetForwardVector()*MaxGrabDistance;
    	DrawDebugLine(GetWorld(),Start,End,FColor::Red);
		DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue,false,5.0f);
    
    	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
    	FHitResult HitResult;
    	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,Start,End,FQuat::Identity,ECC_GameTraceChannel2,Sphere);
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10,10,FColor::Yellow,false,5.0f);
    	if(HasHit)
    	{
    		AActor* ActorHit = HitResult.GetActor();
    		
    		UE_LOG(LogTemp,Warning,TEXT("Actor hit: %s"),*ActorHit->GetActorNameOrLabel());
    	}
    	else
    	{
    		UE_LOG(LogTemp,Warning,TEXT("No Actor was hit!"));
    	}
}

void UGrabberComponent::Release()
{
	UE_LOG(LogTemp,Warning,TEXT("Grabber Released!"))
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandleComponent)
	{
		UE_LOG(LogTemp,Display,TEXT("ComponentName: %s"),*PhysicsHandleComponent->GetName());
	}
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

