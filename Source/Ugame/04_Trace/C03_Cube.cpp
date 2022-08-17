#include "04_Trace/C03_Cube.h"
#include "Global.h"

#include "Components/StaticMeshComponent.h"

AC03_Cube::AC03_Cube()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");


	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Cube.M_Cube'");

	Mesh->SetStaticMesh(mesh);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

}


void AC03_Cube::BeginPlay()
{
	Super::BeginPlay();
	
}

