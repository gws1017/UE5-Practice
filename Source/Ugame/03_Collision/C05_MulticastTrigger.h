#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_MulticastTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiLightBeginOverlap, int32, FLinearColor);


UCLASS()
class UGAME_API AC05_MulticastTrigger : public AActor
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

	AC05_MulticastTrigger();

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:

	FMultiLightBeginOverlap OnMultiLightBeginOverlap;
};
