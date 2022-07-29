// Pupa&Lupa sftwr. All rights reserved!


#include "Characters/SEU_BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SEU_CharacterMovementComponent.h"
#include "Components/SEU_HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Components/SEU_WeaponComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All,All);

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


	//TODO: Rename HealthComponent to ResourceComponent and add Resource as derived objects from component
	HealthComponent = CreateDefaultSubobject<USEU_HealthComponent>("Health Component");
	WeaponComponent = CreateDefaultSubobject<USEU_WeaponComponent>("Weapon Component");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("Health Text");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->bOwnerNoSee = true;

}

// Called when the game starts or when spawned
void ASEU_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());
	OnHealthChanged(HealthComponent->GetHealth()); //explicit call of health changed function for update text render value of health
	HealthComponent->OnDeath.AddUObject(this,&ASEU_BaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this,&ASEU_BaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this,&ASEU_BaseCharacter::OnGroundLanded);
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
	check(PlayerInputComponent);
	check(WeaponComponent);
	
	PlayerInputComponent->BindAxis("MoveForward",this,&ASEU_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASEU_BaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp",this,&ASEU_BaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround",this,&ASEU_BaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASEU_BaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ASEU_BaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released,this,&ASEU_BaseCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USEU_WeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USEU_WeaponComponent::StopFire);
	PlayerInputComponent->BindAction("SwapWeapon", IE_Pressed, WeaponComponent, &USEU_WeaponComponent::SwapWeapon);
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
	const auto CharacterFalling = Cast<USEU_CharacterMovementComponent>(GetComponentByClass(USEU_CharacterMovementComponent::StaticClass()));
	if(!CharacterFalling->IsFalling())
	{
		bIsMovingForward = Scale > 0.f;
		AddMovementInput(GetActorForwardVector(), Scale);
	}
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

void ASEU_BaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacter,Warning, TEXT("Character %s is Dead!"), *GetName());
	GetCharacterMovement()->DisableMovement();
	PlayAnimMontage(DeathMontage);
	SetLifeSpan(LifeSpanOnDeath);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	
}

void ASEU_BaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"),Health)));
}

void ASEU_BaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocity = -GetVelocity().Z;
	UE_LOG(LogBaseCharacter,Display,TEXT("On landed: %f"), FallVelocity);

	if(FallVelocity < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,LandedDamage, FallVelocity);
	UE_LOG(LogBaseCharacter,Display,TEXT("final damage: %f"), FinalDamage);
	TakeDamage(FinalDamage,FDamageEvent{},nullptr,nullptr);
}


