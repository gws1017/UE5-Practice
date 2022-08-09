// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/C02_SpawnActor_Cube.h"
#include "Global.h"

AC02_SpawnActor_Cube::AC02_SpawnActor_Cube()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Cube.M_Cube'");
	Mesh->SetStaticMesh(mesh);
}