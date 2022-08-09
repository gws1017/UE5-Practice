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
	//�����ڸ� �����Ŭ������ ��Ƶδ°�::������Ʈ�� ã����
	//<�ڷ���ã��>
	//TEXT()�����ڵ� ���
	//L ��Ƽ����Ʈ ����1 �ѱ�2
	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Meshes/M_Cone.M_Cone'");
	//Mesh->SetStaticMesh(mesh.Object);

	//mesh use root
	RootComponent = Mesh;
	//�޽� �⺻�ڷ��� / ����������/�޽�����/ť��,�ĺ���
	//StaticMesh'/Game/Meshes/M_Cube.M_Cube'StaticMesh'/Game/Meshes/M_Cone.M_Cone'

	
	//is_mesh = mesh.Succeeded();
	//�޽��� ���������� ã�Ҵٸ� component�� �������ش�
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Cone.M_Cone'");
	Mesh->SetStaticMesh(mesh);
}

void AC02_SpawnActor::BeginPlay()
{
	Super::BeginPlay();

	//c++ ������ MaterialInstance�� MaterialConstant�� ǥ��
	//���� �ε��� �ؾ��ؼ� ���� Ŭ���� ����� �Ұ�����
	//�����ڰ� �ƴѰ����� �����ε��Լ��� StaticLoadObejct
	//UObject�� �ֻ��� �ڷ����̹Ƿ� ����� �ڷ����� ĳ�����ؼ� ���
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), 
	//	NULL, L"MaterialInstanceConstant'/Game/Material/M_Mesh_Inst.M_Mesh_Inst'");
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj); // ĳ���� ���н� NULL����

	//����Ŭ������ ���
	//���̳��� ���͸��� ����, Material��ü�� UMaterialInterface�κ��� ��ӵǾ��� ������
	UMaterialInstanceConstant* material; //�𸮾󿡼��� ������ ����� �ڵ� �ʱ�ȭ���� NULL
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Material/M_Mesh_Inst.M_Mesh_Inst'");
	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0,Material);

	//this = blueprint�� self
	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);
}

void AC02_SpawnActor::ChangeColor()
{
	FLinearColor color;

	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	//material���鶧 �̸��� Color��� ����κ� �ٲٱ�
	Material->SetVectorParameterValue("Color", color);
}

