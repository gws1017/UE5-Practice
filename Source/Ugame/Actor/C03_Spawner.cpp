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
	
	//�𸮾󿡼��� int32�� �����
	//int 4����Ʈ 4*8 = 32
	//pc ���Ӹ� ���۵Ǵ°� �ƴϱ⶧���� ��Ƽ�÷����� �����ؼ� �ڷ��� ũ�⸦ ��ȯ�ϵ���
	//��� �÷������� int ũ�Ⱑ �ٸ� ���մ�

	for (int32 i = 0; i < 3; i++)
	{
		FTransform transfrom;
		FVector location = GetActorLocation();
		transfrom.SetLocation(FVector(location.X+i*400,location.Y,location.Z));
		SpawnActors[i] = GetWorld()->SpawnActor<AC02_SpawnActor>(SpawnClass[i], transfrom);
	}
}


