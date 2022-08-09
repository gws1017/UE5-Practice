#include "03_Collision/C01_ActorBeginOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "C01_ActorBeginOverlap.h"

AC01_ActorBeginOverlap::AC01_ActorBeginOverlap()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "box", Scene);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

}

void AC01_ActorBeginOverlap::BeginPlay()
{
	Super::BeginPlay();
	//��������Ʈ�� �̺�Ʈ�� �Լ��� On�� ���δ�
	//��������Ʈ�� ���ڸ� Ÿ���� �Ȱ��ƾ��Ѵ�. ���̳����� ��� F12�� ã�Ƶ鰨

	OnActorBeginOverlap.AddDynamic(this, &AC01_ActorBeginOverlap::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC01_ActorBeginOverlap::ActorEndOverlap);
}

void AC01_ActorBeginOverlap::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str = "";
	str.Append("C++ Actor Begin Overlap : ");
	str.Append(OtherActor->GetName());

	CLog::Log(str);
}

void AC01_ActorBeginOverlap::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str = "";
	str.Append("C++ Actor End Overlap : ");
	str.Append(OtherActor->GetName());

	CLog::Log(str);
}


