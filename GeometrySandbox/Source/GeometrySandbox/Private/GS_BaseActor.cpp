// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_BaseActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseActor, All,All);

// Sets default values
AGS_BaseActor::AGS_BaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGS_BaseActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogBaseActor, Warning, TEXT("Hello Ureal! Again :)"));
}

// Called every frame
void AGS_BaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

