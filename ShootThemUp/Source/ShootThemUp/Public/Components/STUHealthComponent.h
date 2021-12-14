// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category="Health")
	bool IsDead() const {return FMath::IsNearlyZero(Health);}
	
	float GetHealth() const {return Health;};
	
protected:
	// Called when the game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax="100"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health Regen")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health Regen", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health Regen", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health Regen", meta = (EditCondition = "AutoHeal"))
	float HealAmount = 5.0f;
	
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;
	
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	void HealUpdate();
	void SetHealth(float NewHealth);
};
