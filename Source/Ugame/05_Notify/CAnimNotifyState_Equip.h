#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Equip.generated.h"

/**
 * 
 */
UCLASS()
class UGAME_API UCAnimNotifyState_Equip : public UAnimNotifyState
{
	GENERATED_BODY()
	
public://4.25버전부터는 public:안쓰면 private임

	FString GetNotifyName_Implementation() const;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

};
