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
	//모든값 사용가능
	UPROPERTY(EditAnywhere)
		int A = 10;
	//배치된애들만 사용가능
	UPROPERTY(EditInstanceOnly)
		int B = 20;
	//기본값 설정
	UPROPERTY(EditDefaultsOnly)
		int C = 30;

protected:
	//수정 불가능, 값확인만
	//블루프린트 접근가능(protected필요)
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int test = 50;
public:	
	// Sets default values for this actor's properties
	AC01_Property();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
