// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/C02_SpawnActor.h"
#include "Actor/C03_Spawner.h"
#include "Global.h"
AC03_Spawner::AC03_Spawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC03_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	//언리얼에서는 int32를 사용함
	//int 4바이트 4*8 = 32
	//pc 게임만 제작되는게 아니기때문에 멀티플랫폼을 지원해서 자료형 크기를 변환하도록
	//사용 플랫폼마다 int 크기가 다를 수잇다

	for (int32 i = 0; i < 3; i++)
	{
		FTransform transfrom;
		FVector location = GetActorLocation();
		transfrom.SetLocation(FVector(location.X+i*400,location.Y,location.Z));
		SpawnActors[i] = GetWorld()->SpawnActor<AC02_SpawnActor>(SpawnClass[i], transfrom);
	}
}


