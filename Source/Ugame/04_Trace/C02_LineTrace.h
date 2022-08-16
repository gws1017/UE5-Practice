#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_LineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTraceResult, class AActor*, InActor, FLinearColor, InColor);

UCLASS()
class UGAME_API AC02_LineTrace : public AActor
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	

	AC02_LineTrace();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

private:
	TArray<class AC01_Cylinder*> Cylinders;

private:

	UFUNCTION()
	void StartJump(class AActor* InActor, FLinearColor InColor);

protected:

	UFUNCTION(BlueprintCallable)
	void RestorColor(class ACPlayer* InPlayer);

public:
	UPROPERTY(BlueprintAssignable)
		FTraceResult OnTraceResult;
};
