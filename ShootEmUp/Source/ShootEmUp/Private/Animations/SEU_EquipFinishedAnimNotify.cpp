// Pupa&Lupa sftwr. All rights reserved!


#include "Animations/SEU_EquipFinishedAnimNotify.h"

void USEU_EquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}