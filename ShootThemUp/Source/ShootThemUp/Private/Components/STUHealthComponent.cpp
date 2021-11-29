// Shoot Them Up Game, All Rights Reserved


#include "Components/STUHealthComponent.h"

// Sets default values
ASTUHealthComponent::ASTUHealthComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUHealthComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

