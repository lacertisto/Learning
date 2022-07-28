// Pupa&Lupa sftwr. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SEU_ResourceBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnResourceValueChangedSignature, float);

UENUM()
enum EResourceUpdateBehaviour : uint8
{
	EIncreaseParams,
	EDecreaseParams
};

USTRUCT()
struct FResourceParams
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, VisibleAnywhere, Category = "Resource parameters", 
		meta=(DisplayName="Auto update enabled"))
	bool bUpdateEnabled = false;

	UPROPERTY(EditDefaultsOnly, VisibleAnywhere, Category = "Resource parameters",
		meta = (EditCondition = "bUpdateEnabled", ToolTip="Sets behavior for the resource update events (increase\\decrease)"))
	EResourceUpdateBehaviour UpdateBehaviour = EResourceUpdateBehaviour::EIncreaseParams;

	UPROPERTY(EditDefaultsOnly, VisibleAnywhere, Category = "Resource parameters", 
		meta = (EditCondition="bUpdateEnabled", ClampMin="1.0", ClampMax="100.0", ToolTip="Maximum value on which update will stop"))
	float UpdateMaxThreshold = 1.f;

	UPROPERTY(EditDefaultsOnly, VisibleAnywhere, Category = "Resource parameters",
		meta = (EditCondition = "bUpdateEnabled", ClampMin = "1.0", ClampMax = "100.0",
			ToolTip = "Minimum value on which update will stop"))
	float UpdateMinThreshold = 1.f;

	UPROPERTY(EditDefaultsOnly, VisibleAnywhere, Category = "Resource parameters", 
		meta = (EditCondition="bUpdateEnabled", ClampMin="1.0", ClampMax="100.0", ToolTip="Initial delay before start updating the value"))
	float UpdateInitialDelay = 1.f;

	UPROPERTY(EditDefaultsOnly, VisibleAnywhere, Category = "Resource parameters",
		meta = (EditCondition = "bUpdateEnabled", ClampMin = "1.0", ClampMax = "100.0", ToolTip="Frequency of value updates"))
	float UpdateFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly, VisibleAnywhere, Category = "Resource parameters",
		meta = (EditCondition = "bUpdateEnabled", ClampMin = "1.0", ClampMax = "100.0"))
	float UpdateValue = 1.f;
};

UCLASS()
class SHOOTEMUP_API USEU_ResourceBase : public UObject
{
	GENERATED_BODY()
	
	public:

		FOnResourceValueChangedSignature OnResourceValueChanged;
		
		/** Set or Return whole structure*/
		void SetResourceParams(const FResourceParams& NewResourceParams);
		FResourceParams GetResourceParams() const { return ResourceParams;}

		void SetUpdateBehaviour(const FResourceParams& ResourceParams);
		EResourceUpdateBehaviour GetUpdateBehaviour() const {return ResourceParams.UpdateBehaviour;}

	protected:

		FResourceParams ResourceParams;
		FTimerHandle UpdateValueTimerHandle;

		void UpdateResourceValue(const float DeltaValue);
		void StopTimer(const FTimerHandle& TimerHandle) const;
};
