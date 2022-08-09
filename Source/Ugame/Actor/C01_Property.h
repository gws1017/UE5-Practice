// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Property.generated.h"

UCLASS()
class UGAME_API AC01_Property : public AActor
{
	GENERATED_BODY()
private:
	//��簪 ��밡��
	UPROPERTY(EditAnywhere)
		int A = 10;
	//��ġ�Ⱦֵ鸸 ��밡��
	UPROPERTY(EditInstanceOnly)
		int B = 20;
	//�⺻�� ����
	UPROPERTY(EditDefaultsOnly)
		int C = 30;

protected:
	//���� �Ұ���, ��Ȯ�θ�
	//�������Ʈ ���ٰ���(protected�ʿ�)
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int test = 50;
public:	
	// Sets default values for this actor's properties
	AC01_Property();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
