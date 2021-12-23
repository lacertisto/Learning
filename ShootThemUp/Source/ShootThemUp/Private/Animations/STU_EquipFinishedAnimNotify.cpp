// Shoot Them Up Game, All Rights Reserved


#include "Animations/STU_EquipFinishedAnimNotify.h"

void USTU_EquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotify.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
