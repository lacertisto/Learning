// Pupa&Lupa sftwr. All rights reserved!


#include "Characters/SEU_BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SEU_CharacterMovementComponent.h"

// Modified constructor with calling parent constructor and passing new movement component class to override configurations
ASEU_BaseCharacter::ASEU_BaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USEU_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASEU_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ASEU_BaseCharacter::IsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
}

float ASEU_BaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.f;
	//calculate normalized velocity vector
	const auto VelocityNormal = GetVelocity().GetSafeNormal(); 
	//calculate angle between current point and velocity vector (in RADIANS)
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(),VelocityNormal));
	//calculate orthogonal vector to both our vetors
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(),VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	//return degrees with sign
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASEU_BaseCharacter::MoveForward(float Scale)
{
	bIsMovingForward = Scale > 0.f;
	AddMovementInput(GetActorForwardVector(), Scale);
}

void ASEU_BaseCharacter::MoveRight(float Scale)
{
	AddMovementInput(GetActorRightVector(), Scale);
}

void ASEU_BaseCharacter::OnStartRunning()
{
	bWantsToRun = true;
}

void ASEU_BaseCharacter::OnStopRunning()
{
	bWantsToRun = false;
}

// Called every frame
void ASEU_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASEU_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASEU_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASEU_BaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp",this,&ASEU_BaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround",this,&ASEU_BaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASEU_BaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ASEU_BaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released,this,&ASEU_BaseCharacter::OnStopRunning);
}

