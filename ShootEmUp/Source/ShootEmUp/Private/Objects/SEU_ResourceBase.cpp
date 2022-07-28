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

void USEU_ResourceBase::SetUpdateBehaviour(const FResourceParams& ResourceParams)
{
	
}

void USEU_ResourceBase::StopTimer(const FTimerHandle& TimerHandle) const
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if(TimerManager.IsTimerActive(UpdateValueTimerHandle))
	{
		TimerManager.ClearTimer(UpdateValueTimerHandle);
	}
}

void ESEU_ResourceBase::UpdateResourceValue()
{

}