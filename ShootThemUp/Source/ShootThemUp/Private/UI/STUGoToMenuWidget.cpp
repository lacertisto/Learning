// Shoot Them Up Game, All Rights Reserved


#include "UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMainMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized()
{
	if(MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnMainMenuChosed);
	}
}

void USTUGoToMenuWidget::OnMainMenuChosed()
{
	if(!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();

	if(STUGameInstance->GetMainMenuLevelname().IsNone()) 
	{
		UE_LOG(LogSTUMainMenuWidget, Error, TEXT("There is no level with name None!"));	
		return;
	}

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetMainMenuLevelname());
	
	
	
}


