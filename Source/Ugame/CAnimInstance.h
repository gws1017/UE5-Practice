// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UGAME_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	//BlueprintReadOnly : 블루프린트 읽기 전용
	//액터가 아닌 클래스에서 에디터 ㅂ변수를 공개할때
	//이렇게 해야 에디터에 나타남
	UPROPERTY(BlueprintReadOnly, EditAnywhere,Category = "Animation")
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Direction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Pitch;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		bool bEquipped;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		bool bAiming;


public:
	virtual void NativeBeginPlay() override;
	//override 키워드가 언리얼에서는 필수임 생략불가능

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACharacter* OwnerCharacter;
};
