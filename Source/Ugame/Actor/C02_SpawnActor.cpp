// Fill out your copyright notice in the Description page of Project Settings.


#include "Ugame/Actor/C02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AC02_SpawnActor::AC02_SpawnActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	//생성자를 도움될클래스를 모아두는곳::오브젝트를 찾아줌
	//<자료형찾기>
	//TEXT()유니코드 방식
	//L 멀티바이트 영문1 한글2
	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Meshes/M_Cone.M_Cone'");
	//Mesh->SetStaticMesh(mesh.Object);

	//mesh use root
	RootComponent = Mesh;
	//메쉬 기본자료형 / 컨텐츠폴더/메쉬폴더/큐브,식별자
	//StaticMesh'/Game/Meshes/M_Cube.M_Cube'StaticMesh'/Game/Meshes/M_Cone.M_Cone'

	
	//is_mesh = mesh.Succeeded();
	//메쉬를 성공적으로 찾았다면 component에 설정해준다
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Cone.M_Cone'");
	Mesh->SetStaticMesh(mesh);
}

void AC02_SpawnActor::BeginPlay()
{
	Super::BeginPlay();

	//c++ 에서는 MaterialInstance가 MaterialConstant로 표현
	//동적 로딩을 해야해서 헬퍼 클래스 사용이 불가능함
	//생성자가 아닌곳에서 동적로딩함수는 StaticLoadObejct
	//UObject는 최상위 자료형이므로 사용할 자료형을 캐스팅해서 사용
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), 
	//	NULL, L"MaterialInstanceConstant'/Game/Material/M_Mesh_Inst.M_Mesh_Inst'");
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj); // 캐스팅 실패시 NULL리턴

	//헬퍼클래스로 사용
	//다이나믹 머터리얼 생성, Material전체는 UMaterialInterface로부터 상속되어져 구현됨
	UMaterialInstanceConstant* material; //언리얼에서는 포인터 선언시 자동 초기화해줌 NULL
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Material/M_Mesh_Inst.M_Mesh_Inst'");
	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0,Material);

	//this = blueprint의 self
	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);
}

void AC02_SpawnActor::ChangeColor()
{
	FLinearColor color;

	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	//material만들때 이름을 Color라고 만든부분 바꾸기
	Material->SetVectorParameterValue("Color", color);
}

