// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CaracalPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ACaracalPawn::ACaracalPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	MeshComponent->Mobility = EComponentMobility::Movable;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(MeshComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(0.f, -10.f, 0.f));
	SpringArmComponent->SetRelativeLocation(FVector(6.f, 0.f, 30.f));
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->TargetOffset = FVector(0.f, 50.f, 100.f);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeRotation(FRotator(0.f, -10.f, 0.f));
	CameraComponent->FieldOfView = 110.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CurrentVelocity = FVector(0.f);
}

// Called when the game starts or when spawned
void ACaracalPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACaracalPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void ACaracalPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &ACaracalPawn::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveRightLeft"), this, &ACaracalPawn::MoveRightLeft);
//	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, );
}

void ACaracalPawn::MoveForwardBackward(float Value)
{
	CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
}

void ACaracalPawn::MoveRightLeft(float Value)
{
	CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
}
