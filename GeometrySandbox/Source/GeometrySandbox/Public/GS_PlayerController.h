// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GEOMETRYSANDBOX_API AGS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
private:

	UPROPERTY()
	TArray<AActor*> Pawns;

	int32 CurrentPawnIndex = 0;
	
	void SwitchPawn();
};
