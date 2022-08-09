// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Global.h"
ACGameMode::ACGameMode()
{
	//DefaultPawnClass : 기본 플레이어 클래스를 입력받을 변수
	//TSubclassOf<APawn>으로 상속받은 하위 클래스 타입 입력

	//Blueprint'/Game/BP_CPlayer.BP_CPlayer'
	//블루프린트 클래스타입을 쓸때는 _C를 꼭붙일것

	//ConstructorHelpers::FClassFinder<APawn> pawn(L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
	//
	//if(pawn.Succeeded())
	//	
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
}