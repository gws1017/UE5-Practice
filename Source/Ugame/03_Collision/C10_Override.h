#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C10_Override.generated.h"

UCLASS()
class UGAME_API AC10_Override : public AActor
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

	AC10_Override();

protected:

	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintImplementableEvent) //�Լ��� �������Ʈ���� �����ؼ� ����
		void ChangeColorRed();
	UFUNCTION(BlueprintNativeEvent)
		void ChangeColorWhite();
		void ChangeColorWhite_Implementation();
private:

	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
