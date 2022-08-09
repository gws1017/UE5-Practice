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
	//BlueprintReadOnly : ��������Ʈ �б� ����
	//���Ͱ� �ƴ� Ŭ�������� ������ �������� �����Ҷ�
	//�̷��� �ؾ� �����Ϳ� ��Ÿ��
	UPROPERTY(BlueprintReadOnly, EditAnywhere,Category = "Animation")
		float Speed;

public:
	virtual void NativeBeginPlay() override;
	//override Ű���尡 �𸮾󿡼��� �ʼ��� �����Ұ���

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACharacter* OwnerCharacter;
};