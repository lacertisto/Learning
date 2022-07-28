// Pupa&Lupa sftwr. All rights reserved!


#include "Objects/SEU_ResourceBase.h"
#include "Engine/World.h"
#include "TimerManager.h"

void USEU_ResourceBase::SetResourceParams(const FResourceParams& NewResourceParams)
{
	ResourceParams = NewResourceParams;
	
	if(ResourceParams.bUpdateEnabled == true)
	{
		GetWorld()->GetTimerManager().SetTimer(UpdateValueTimerHandle, ResourceParams.UpdateFrequency, true, ResourceParams.UpdateInitialDelay);
	}
}

void USEU_ResourceBase::StopTimer(FTimerHandle& TimerHandle) const
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if(TimerManager.IsTimerActive(TimerHandle))
	{
		TimerManager.ClearTimer(TimerHandle);
	}
}

void USEU_ResourceBase::UpdateResourceValue(float DeltaValue)
{

}