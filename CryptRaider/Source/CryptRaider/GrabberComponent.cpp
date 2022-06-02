// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
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
	UPhysicsHandleComponent* PhysicsHandleComponent = GetPhysicsHandleComponent();
	if(!PhysicsHandleComponent) return;
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
    		HitResult.GetComponent()->SetSimulatePhysics(true);
    		HitResult.GetComponent()->WakeAllRigidBodies();
    		HitResult.GetActor()->Tags.Add("Grabbed");
    		HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(
    			HitResult.GetComponent(),
    			NAME_None,
    			HitResult.ImpactPoint,
    			GetComponentRotation());
    	}
}

void UGrabberComponent::Release()
{
	UPhysicsHandleComponent* PhysComponent = GetPhysicsHandleComponent();
	if(!PhysComponent) return;
	if(PhysComponent->GetGrabbedComponent())
	{
		PhysComponent->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		PhysComponent->ReleaseComponent();
	}
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();


}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandleComponent() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(!GetPhysicsHandleComponent()) return;
	if(GetPhysicsHandleComponent()->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector().GetSafeNormal()*HoldDistance;
		GetPhysicsHandleComponent()->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

