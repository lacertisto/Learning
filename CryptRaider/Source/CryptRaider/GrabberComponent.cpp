// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

#include <string>


// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UGrabberComponent::PrintDamage(const float& Damage)
{
	UE_LOG(LogTemp,Warning,TEXT("%f"),Damage)
}

bool UGrabberComponent::HasDamage(float& OutDamage)
{
	OutDamage = 5;
	return true;
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	
	DrawDebugLine(GetWorld(),Start, End, FColor::Red);

	float Damage;
	if(HasDamage(Damage)) PrintDamage(Damage);
}

