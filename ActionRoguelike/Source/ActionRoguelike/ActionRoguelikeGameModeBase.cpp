// Copyright Epic Games, Inc. All Rights Reserved.


#include "ActionRoguelikeGameModeBase.h"
#include "Characters/ARCharacter.h"

AActionRoguelikeGameModeBase::AActionRoguelikeGameModeBase()
{
	DefaultPawnClass = AARCharacter::StaticClass();
}

