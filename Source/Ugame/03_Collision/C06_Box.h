// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C06_Box.generated.h"

UCLASS()
class UGAME_API AC06_Box : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh[3];
public:	

	AC06_Box();

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnPhysics(int32 InIndex, FLinearColor InColor);
private:

	UMaterialInstanceDynamic* Materials[3];

	FVector WorldLocation[3];
//
//	UFUNCTION()
//		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
//	UFUNCTION()
//		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
