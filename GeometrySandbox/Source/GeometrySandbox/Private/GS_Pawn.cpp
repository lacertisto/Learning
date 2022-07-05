// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_Pawn.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogGSPawn, All, All);

// Sets default values
AGS_Pawn::AGS_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());
	
}

void AGS_Pawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(!NewController) return;
	UE_LOG(LogGSPawn, Warning, TEXT("Pawn %s possessed by %s"), *GetName(), *NewController->GetName());
}

void AGS_Pawn::UnPossessed()
{
	Super::UnPossessed();

	UE_LOG(LogGSPawn, Warning, TEXT("Pawn %s unpossessed"), *GetName());
}

// Called when the game starts or when spawned
void AGS_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGS_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!VelocityVector.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
		VelocityVector = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void AGS_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(!PlayerInputComponent) return;
	PlayerInputComponent->BindAxis("MoveForward",this,&AGS_Pawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &AGS_Pawn::MoveRight);
}

void AGS_Pawn::MoveForward(float Scale)
{
	VelocityVector.X = Scale;
}

void AGS_Pawn::MoveRight(float Scale)
{
	VelocityVector.Y = Scale;
}

