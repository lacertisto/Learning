// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEU_DevDamageActor.generated.h"

UCLASS()
class SHOOTEMUP_API ASEU_DevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASEU_DevDamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Radius = 300.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 30.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bDoFullDamage = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
