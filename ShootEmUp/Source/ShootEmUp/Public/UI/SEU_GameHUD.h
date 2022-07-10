// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SEU_GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API ASEU_GameHUD : public AHUD
{
	GENERATED_BODY()
	
	public:
	virtual void DrawHUD() override;

	private:
	void DrawCrosshair();
};
