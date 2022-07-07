// Pupa&Lupa sftwr. All rights reserved!


#include "SEU_GameModeBase.h"
#include "Characters/SEU_BaseCharacter.h"
#include "Characters/SEU_PlayerController.h"


ASEU_GameModeBase::ASEU_GameModeBase()
{
	DefaultPawnClass = ASEU_BaseCharacter::StaticClass();
	PlayerControllerClass = ASEU_PlayerController::StaticClass();
}
