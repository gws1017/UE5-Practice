#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Cube.generated.h"

UCLASS()
class UGAME_API AC03_Cube : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
public:	

	AC03_Cube();

protected:

	virtual void BeginPlay() override;

};
