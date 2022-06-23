// Copyright Epic Games, Inc. All Rights Reserved.


#include "SimpleShooterGameModeBase.h"

#include "Characters/SSBaseCharacter.h"
#include "Characters/SSPlayerController.h"

ASimpleShooterGameModeBase::ASimpleShooterGameModeBase()
{
	PlayerControllerClass = ASSPlayerController::StaticClass();
	DefaultPawnClass = ASSBaseCharacter::StaticClass();
}

void ASimpleShooterGameModeBase::PawnKilled(APawn* PawnKilled)
{
	
}
