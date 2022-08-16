#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Cylinder.generated.h"

UCLASS()
class UGAME_API AC01_Cylinder : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
public:	

	AC01_Cylinder();

protected:

	virtual void BeginPlay() override;


};
