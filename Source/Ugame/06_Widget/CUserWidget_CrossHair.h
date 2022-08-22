#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_CrossHair.generated.h"


UCLASS()
class UGAME_API UCUserWidget_CrossHair : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnFocus();
	UFUNCTION(BlueprintImplementableEvent)
		void OffFocus();
};

