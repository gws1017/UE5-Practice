#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C09_Particles.generated.h"

UCLASS()
class UGAME_API AC09_Particles : public AActor
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystem* Particles[3];
public:	

	AC09_Particles();

protected:

	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void PlayParticle(int32 InIndex);
};
