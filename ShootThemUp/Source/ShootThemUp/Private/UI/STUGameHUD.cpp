// Shoot Them Up Game, All Rights Reserved


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();

	// DrawCrossHair();
}

void ASTUGameHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if(PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();	
	}
	if(GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
		}
	}
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

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State)
{
	UE_LOG(LogSTUGameHUD, Display, TEXT("Match state changed: %s"),*UEnum::GetValueAsString(State));
}
