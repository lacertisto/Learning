// Shoot Them Up Game, All Rights Reserved


#include "AI/Services/STUWeaponSwapService.h"
#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

USTUWeaponSwapService::USTUWeaponSwapService()
{
	NodeName = "Swap Weapon";
}

void USTUWeaponSwapService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	
	const auto Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
    }

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
