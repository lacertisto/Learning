// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	//bind to actor delegate ontakeanydamage
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	TanksGameMode = Cast<ATanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy
	, AActor* DamageCauser)
{
	if(Damage <= 0.f) return;
	
	Health -= Damage;

	if(Health <= 0.f && DamagedActor && TanksGameMode)
	{
		TanksGameMode->ActorDied(DamagedActor);
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

