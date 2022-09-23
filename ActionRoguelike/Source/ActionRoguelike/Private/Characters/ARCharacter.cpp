// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AARCharacter::AARCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;
}

void AARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AARCharacter::Jump)
}

void AARCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(),Value);
}

void AARCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
