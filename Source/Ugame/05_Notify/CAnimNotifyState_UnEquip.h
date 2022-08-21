#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_UnEquip.generated.h"


UCLASS()
class UGAME_API UCAnimNotifyState_UnEquip : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	
	//AnimNoitfy 이름이 어떻게노출되는지 재정의
	FString GetNotifyName_Implementation() const;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
