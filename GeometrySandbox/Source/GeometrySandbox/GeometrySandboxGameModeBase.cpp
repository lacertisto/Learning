// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandboxGameModeBase.h"

#include "GS_Pawn.h"
#include "GS_PlayerController.h"

AGeometrySandboxGameModeBase::AGeometrySandboxGameModeBase()
{
	DefaultPawnClass = AGS_Pawn::StaticClass();
	PlayerControllerClass = AGS_PlayerController::StaticClass();
}
