// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::SetMover(UMoverComponent* NewMover)
{
	Mover = NewMover;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if(Actor != nullptr && !Actor->ActorHasTag("Grabbed"))
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if(Component)
		{
			Component->SetSimulatePhysics(false);
			Component->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
		}
		Mover->SetShouldMove(true);
	}
	else
	{
		
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	
	for(AActor*& Actor : Actors)
	{
		if(Actor->ActorHasTag(ActorTag))
		{
			return Actor;
		}
	}
	return nullptr;
}
