// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SSAIController.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASSAIController();
	
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;
	
protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehaviorTree;
	
};
