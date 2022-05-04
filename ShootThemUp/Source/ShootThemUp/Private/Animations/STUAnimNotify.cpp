// Shoot Them Up Game, All Rights Reserved


#include "Animations/STUAnimNotify.h"


void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotify.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation,);
}
