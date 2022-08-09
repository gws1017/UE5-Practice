#include "02_Debug/C01_Log.h"
#include "Global.h"
AC01_Log::AC01_Log()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC01_Log::BeginPlay()
{
	Super::BeginPlay();
	
	CLog::Print(10);
	CLog::Print(20, 1);
	//같은 key면 30이 빠르게 지워짐
	CLog::Print(30, 2, 20.0f);
	CLog::Print(40, 2, 20.0f);

	CLog::Print("Unreal Gameplay sexsex");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

	CLog::Log(10);
	CLog::Log(PI);
	CLog::Log("Unreal Gameplay sex");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());

	CLog::Log(this);
	//컴파일할때 해당 매크로가 소속된 정보를 나타냄
	PrintLine();
}

void AC01_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;

	CLog::Print(Time, 3);
}

