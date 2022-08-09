// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Spawner.generated.h"

UCLASS()
class UGAME_API AC03_Spawner : public AActor
{
	GENERATED_BODY()
private:
	//TSubclassOf 해당자료형 전방선언
	//리플렉션
	//자료형의 타입을 변수로 다룰 수있도록 하는 기능
	//스폰액터 상속받은 클래스만 사용할수 있게 제한
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC02_SpawnActor> SpawnClass[3];
		//UClass* SpawnClass;
		//UClass는 언리얼 모든 클래스 가능;
public:	
	AC03_Spawner();

protected:
	virtual void BeginPlay() override;

private:
	class AC02_SpawnActor* SpawnActors[3];
	
};
