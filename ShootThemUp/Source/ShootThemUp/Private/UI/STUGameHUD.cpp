// Shoot Them Up Game, All Rights Reserved


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f); // Getting center of a screen

	const float HalfLineSize = 10.0f; // constant for accomplishing crosshair size
	const float LineThickness = 2.0f; // constant for accomplishing crosshair thickness
	const FLinearColor LineColor = FLinearColor::Green; //crosshair color
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness); //draw crosshair element on X line
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness); // same for Y line

	
}
