#pragma once
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

// 자주 사용하는것은 템플릿으로 만들어서 편하게 사용하자
class UGAME_API CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		//오류가 났을 때 개발중에 오류값 체크
		//에디터상에서 사용
		//실제 게임내에서는 실행되지않는 디버깅용
		verifyf(asset.Succeeded(), L"asset.Succeeded()");
		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(),NULL, *InPath));
		//!!obj == obj != NULL
		//언리얼에서는 같은 표현임
		verifyf(!!obj, L"!!obj");
		*OutObject = obj;
	}

	template<typename T>
	static void CreateComponent(AActor* InActor, T** InComponent,
		FName InName, USceneComponent* InParent = NULL)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*InComponent)->SetupAttachment(InParent);
			return;
		}

		InActor->SetRootComponent((*InComponent));
	}

	template<typename T>//기본적으로 TSub클래스가 포인터임.
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);

		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}
};