#include "03_Collision/C07_SpotLight.h"
#include "C05_MulticastTrigger.h"
#include "Global.h"

#include "Components/TextRenderComponent.h"
#include "Components/SpotLightComponent.h"

AC07_SpotLight::AC07_SpotLight()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("SpotLight_");
		str.Append(FString::FromInt(i + 1));
		CHelpers::CreateComponent<USpotLightComponent>(this, &SpotLight[i], FName(str), Scene);

		SpotLight[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		SpotLight[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		SpotLight[i]->Intensity = 1e+5f;
		SpotLight[i]->OuterConeAngle = 25.f;
	}
}

void AC07_SpotLight::BeginPlay()
{
	Super::BeginPlay();

	TArray<AC05_MulticastTrigger*> triggers;
	CHelpers::FindActors<AC05_MulticastTrigger>(GetWorld(), triggers);

	//싱글하고 다르게 AddUFunction
	triggers[0]->OnMultiLightBeginOverlap.AddUFunction(this, "OnLightColor");

	
}

void AC07_SpotLight::OnLightColor(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
		SpotLight[i]->SetLightColor(FLinearColor(1, 1, 1));

	SpotLight[InIndex]->SetLightColor(InColor);
}


