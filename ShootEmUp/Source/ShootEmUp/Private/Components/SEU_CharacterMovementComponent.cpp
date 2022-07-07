// Pupa&Lupa sftwr. All rights reserved!


#include "Components/SEU_CharacterMovementComponent.h"
#include "Characters/SEU_BaseCharacter.h"

float USEU_CharacterMovementComponent::GetMaxSpeed() const
{
	
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASEU_BaseCharacter* Player = Cast<ASEU_BaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
