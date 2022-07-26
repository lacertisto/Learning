// Pupa&Lupa sftwr. All rights reserved!


#include "Components/SEU_HealthComponent.h"

#include "SEU_BaseCharacter.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"
// #include "Dev/SEU_FireDamageType.h"
// #include "Dev/SEU_IceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All);
// Sets default values for this component's properties
USEU_HealthComponent::USEU_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USEU_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetHealth(MaxHealth);
	AActor* ComponentOwner = GetOwner();
	if(ComponentOwner)	ComponentOwner->OnTakeAnyDamage.AddDynamic(this,&USEU_HealthComponent::OnTakeAnyDamage);
}

void USEU_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType
	, class AController* InstigatedBy, AActor* DamageCauser)
{
	
	if(Damage <= 0.f || IsDead()) return;
	SetHealth(Health - Damage);
	if(IsDead())
	{
		OnDeath.Broadcast();
	}
	else if(AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&USEU_HealthComponent::Heal, HealUpdateTime, true, HealDelay);
	}

}

void USEU_HealthComponent::Heal()
{
	SetHealth(Health + HealAmount);

	if(FMath::IsNearlyEqual(Health, MaxHealth) || IsDead())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USEU_HealthComponent::SetHealth(float HealthAmount)
{
	Health = FMath::Clamp(HealthAmount,0.f,MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
