#include "03_Collision/C02_ComponentBeginOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"
#include "C02_ComponentBeginOverlap.h"

AC02_ComponentBeginOverlap::AC02_ComponentBeginOverlap()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "box", Scene);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Scene);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	PointLight->SetLightColor(FLinearColor::Red);
}

void AC02_ComponentBeginOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility(false);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC02_ComponentBeginOverlap::ComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AC02_ComponentBeginOverlap::ComponentEndOverlap);
}

void AC02_ComponentBeginOverlap::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLight->SetVisibility(true);

}

void AC02_ComponentBeginOverlap::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLight->SetVisibility(false);

}



