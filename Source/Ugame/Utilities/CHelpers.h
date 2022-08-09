#pragma once
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

// ���� ����ϴ°��� ���ø����� ���� ���ϰ� �������
class UGAME_API CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		//������ ���� �� �����߿� ������ üũ
		//�����ͻ󿡼� ���
		//���� ���ӳ������� ��������ʴ� ������
		verifyf(asset.Succeeded(), L"asset.Succeeded()");
		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(),NULL, *InPath));
		//!!obj == obj != NULL
		//�𸮾󿡼��� ���� ǥ����
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

	template<typename T>//�⺻������ TSubŬ������ ��������.
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);

		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}
};