// Shoot Them Up Game, All Rights Reserved


#include "AI/Decorators/STUAmmoExtinguishDecorator.h"
#include "AIController.h"
#include "STUUtils.hpp"
#include "Components/STUWeaponComponent.h"


USTUAmmoExtinguishDecorator::USTUAmmoExtinguishDecorator()
{
	NodeName = "Need Ammo";
}

bool USTUAmmoExtinguishDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}
