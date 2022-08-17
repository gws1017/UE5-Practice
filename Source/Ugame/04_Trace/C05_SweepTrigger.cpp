#include "04_Trace/C05_SweepTrigger.h"
#include "Global.h"
#include "C04_Explosion.h"

#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC05_SweepTrigger::AC05_SweepTrigger()
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


void AC05_SweepTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AC04_Explosion*> explosions;
	CHelpers::FindActors(GetWorld(), explosions);

	OnActorBeginOverlap.AddDynamic(explosions[0], &AC04_Explosion::ActorBeginOverlap);

}

