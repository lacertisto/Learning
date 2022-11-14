// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CARACAL_API UMyObject : public UObject
{
	GENERATED_BODY()

public:

	UMyObject();

	UPROPERTY(BlueprintReadOnly, Category = "My | Variables")
	float MyFloat;

	UFUNCTION(BlueprintCallable, Category = "My | Functions")
	void MyFunction();
};
