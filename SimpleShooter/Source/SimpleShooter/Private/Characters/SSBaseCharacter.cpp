// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SSBaseCharacter.h"

#include "Weapons/SSBaseWeapon.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"

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

	Health = MaxHealth;
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

bool ASSBaseCharacter::IsDead() const
{
	return Health <=0;
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


float ASSBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator
	, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(!DamageApplied) return 0.f;

	DamageApplied = FMath::Min(Health,DamageApplied);
	Health -= DamageApplied;

	UE_LOG(LogTemp,Warning,TEXT("Health left %f"), Health);
	if(IsDead())
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>()->PawnKilled(this);
	}
	
	return DamageApplied;
}
