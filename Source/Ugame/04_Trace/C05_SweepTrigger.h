#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_SweepTrigger.generated.h"

UCLASS()
class UGAME_API AC05_SweepTrigger : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	

	AC05_SweepTrigger();

protected:

	virtual void BeginPlay() override;


};
