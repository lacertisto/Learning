// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEU_HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

//tick is no need here, so it would be none here
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTEMUP_API USEU_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USEU_HealthComponent();

	float GetHealth() const { return Health;}

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health);}
	
	FOnDeath OnDeath;
	
	FOnHealthChanged OnHealthChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin="1.0",ClampMax="1000.0"))
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Health")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Health",meta=(ClampMin="0.1",ClampMax="10.0", EditCondition="AutoHeal"))
	float HealDelay = 3.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Health", meta=(EditCondition="AutoHeal"))
	float HealUpdateTime = 1.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Health", meta=(EditCondition="AutoHeal"));
	float HealAmount = 1.f;
	
private:
	float Health = 0.f;
	
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy
		, AActor* DamageCauser);

	void Heal();
	void SetHealth(float HealthAmount);
	
	FTimerHandle HealTimerHandle;
};
