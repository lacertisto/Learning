// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObjects/MyObject.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyObject, All, All);

UMyObject::UMyObject()
{
	MyFloat = 0.7f;
}

void UMyObject::MyFunction()
{
	UE_LOG(LogMyObject, Warning, TEXT("This is my float value: %f"), MyFloat);
}