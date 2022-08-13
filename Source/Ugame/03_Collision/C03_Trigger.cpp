#include "03_Collision/C03_Trigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "C03_Trigger.h"

AC03_Trigger::AC03_Trigger()
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

void AC03_Trigger::BeginPlay()
{
	Super::BeginPlay();


	OnActorBeginOverlap.AddDynamic(this, &AC03_Trigger::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC03_Trigger::ActorEndOverlap);
}

void AC03_Trigger::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//IsBound ��������Ʈ�� �Լ��� �ϳ��� ����Ǿ� �ִ��� üũ
	if (OnBoxLightBeginOverlap.IsBound())
		OnBoxLightBeginOverlap.Execute(); //�̱� ĳ��Ʈ���� ����� �Լ��� ����

	if (OnBoxLightRandomBeginOverlap.IsBound())
	{
		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		FString str = OnBoxLightRandomBeginOverlap.Execute(color);
		CLog::Log(str);
	};

}

void AC03_Trigger::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnBoxLightEndOverlap.IsBound())
		OnBoxLightEndOverlap.Execute();
}



