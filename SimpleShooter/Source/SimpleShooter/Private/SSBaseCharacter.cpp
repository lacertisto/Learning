// Fill out your copyright notice in the Description page of Project Settings.


#include "SSBaseCharacter.h"

#include "SSBaseWeapon.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASSBaseCharacter::ASSBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ASSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<ASSBaseWeapon>(WeaponClass);
	//hide the previous weapon
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	//Attaching weapon to the socket of the character
	Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	Weapon->SetOwner(this);
}

void ASSBaseCharacter::Strafe(float Scale)
{
	if(Scale == 0.f) return;
	AddMovementInput(GetActorRightVector(),Scale);
}

void ASSBaseCharacter::Move(float Scale)
{
	if(Scale == 0.f) return;
	AddMovementInput(GetActorForwardVector(),Scale);
}

void ASSBaseCharacter::LookUp(float Scale)
{
	if(Scale == 0.f) return;
	AddControllerPitchInput(Scale * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ASSBaseCharacter::LookRight(float X)
{
	if(X == 0.f) return;
	AddControllerYawInput(X * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ASSBaseCharacter::Shoot()
{
	Weapon->Fire();
}

// Called every frame
void ASSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ASSBaseCharacter::Move);
	PlayerInputComponent->BindAxis(TEXT("StrafeRight"),this,&ASSBaseCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&ASSBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSide"),this,&ASSBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&ASSBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"),this,&ASSBaseCharacter::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&ASSBaseCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ASSBaseCharacter::Shoot);
}

