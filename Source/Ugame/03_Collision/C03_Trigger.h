#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Trigger.generated.h"

//델리게이트 : 싱글 델리게이트,멀티캐스트
//싱글델리게이트 : 하나의 함수에 하나의 델리게이트
//멀티캐스트 : 하나의 델리게이트에 여러개 함수가 동작

//델리게이트 매크로
DECLARE_DELEGATE(FBoxLightBeginOverlap); //void _(void)
DECLARE_DELEGATE(FBoxLightEndOverlap); 
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightRandomBeginOverlap, FLinearColor);
UCLASS()
class UGAME_API AC03_Trigger : public AActor
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

	AC03_Trigger();

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	//이름은 뒤쪽 아무거나 상관없음
	//편할려고 F -> On 으로 바꿔준다
	FBoxLightBeginOverlap OnBoxLightBeginOverlap;
	FBoxLightEndOverlap OnBoxLightEndOverlap;
	FBoxLightRandomBeginOverlap OnBoxLightRandomBeginOverlap;
};