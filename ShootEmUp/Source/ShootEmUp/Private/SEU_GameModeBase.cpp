// Pupa&Lupa sftwr. All rights reserved!


#include "SEU_GameModeBase.h"
#include "Characters/SEU_BaseCharacter.h"
#include "Characters/SEU_PlayerController.h"
#include "UI/SEU_GameHUD.h"


ASEU_GameModeBase::ASEU_GameModeBase()
{
	DefaultPawnClass = ASEU_BaseCharacter::StaticClass();
	PlayerControllerClass = ASEU_PlayerController::StaticClass();
	HUDClass = ASEU_GameHUD::StaticClass();
}
