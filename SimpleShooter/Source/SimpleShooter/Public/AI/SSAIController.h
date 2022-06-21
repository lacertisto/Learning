// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SSAIController.generated.h"

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
	
protected:
	virtual void BeginPlay() override;

private:
	
};
