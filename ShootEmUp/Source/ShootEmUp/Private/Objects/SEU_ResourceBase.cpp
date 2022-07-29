// Pupa&Lupa sftwr. All rights reserved!


#include "Objects/SEU_ResourceBase.h"
#include "Engine/World.h"
#include "TimerManager.h"

void USEU_ResourceBase::SetResourceParams(const FResourceParams& NewResourceParams)
{
	ResourceParams = NewResourceParams;
	
	UpdateTimerState(ResourceParams.bUpdateEnabled);
}

void USEU_ResourceBase::HandleDamage(float& Damage)
{

}

/**
	
*/
void USEU_ResourceBase::UpdateTimerState(const bool bActivate)
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (bActivate)
	{
		TimerManager.SetTimer(
			UpdateValueTimerHandle, ResourceParams.UpdateFrequency, true, ResourceParams.UpdateInitialDelay);
	}
	else
	{
		TimerManager.ClearTimer(UpdateValueTimerHandle);
	}
}

void USEU_ResourceBase::UpdateResourceValue(float DeltaValue)
{

}