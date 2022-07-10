// Pupa&Lupa sftwr. All rights reserved!


#include "UI/SEU_GameHUD.h" 
#include "Engine/Canvas.h"

void ASEU_GameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrosshair();
}

void ASEU_GameHUD::DrawCrosshair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX * 0.5, SizeY * 0.5);
	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.f;
	const FLinearColor LineColor = FLinearColor::Red;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);

}
