// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SEU_BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USEU_CharacterMovementComponent;
class USEU_HealthComponent;
class UTextRenderComponent;
class UAnimMontage;

UCLASS()
class SHOOTEMUP_API ASEU_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASEU_BaseCharacter(const FObjectInitializer& ObjInit);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable,Category="Movement")
	float GetMovementDirection() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USEU_HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Animation")
	UAnimMontage* DeathMontage;
	
private:

	void MoveForward(float Scale);
	void MoveRight(float Scale);
	void OnStartRunning();
	void OnStopRunning();

	bool bWantsToRun = false;
	bool bIsMovingForward = false;
	
	void OnDeath();
	void OnHealthChanged(float Health);
};

