#include "03_Collision/C05_MulticastTrigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC05_MulticastTrigger::AC05_MulticastTrigger()
{

}

void AC05_MulticastTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AC05_MulticastTrigger::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC05_MulticastTrigger::ActorEndOverlap);
}

void AC05_MulticastTrigger::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnMultiLightBeginOverlap.IsBound())
	{
		int32 index = UKismetMathLibrary::RandomFloatInRange(0, 1);

		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		OnMultiLightBeginOverlap.Broadcast(index, color);
	}
}

void AC05_MulticastTrigger::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}
