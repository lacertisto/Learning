// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetCurrentAmmoData(FAmmoData& AmmoData) const;

private:
	UFUNCTION(BlueprintCallable, Category="UI")
	USTUWeaponComponent* GetCurrentWeaponComponent() const;
};
