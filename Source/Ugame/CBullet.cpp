#include "CBullet.h"
#include "Global.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"


ACBullet::ACBullet()
{
	CHelpers::CreateComponent(this, &Mesh, "Mesh");
	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Sphere.M_Sphere'");
	Mesh->SetStaticMesh(mesh);

	UMaterialInstanceConstant* material;
	CHelpers::GetAsset <UMaterialInstanceConstant> (&material, "MaterialInstanceConstant'/Game/Material/M_Bullet_Inst.M_Bullet_Inst'");
	Mesh->SetMaterial(0,material);

	Mesh->SetRelativeScale3D(FVector(1.0f, 0.025f, 0.025f));

	Projectile->InitialSpeed = 2e+4f;
	Projectile->MaxSpeed = 2e+4f;
	Projectile->ProjectileGravityScale = 0.0f;

	//물리에의해 업데이트되도록 처리
	Projectile->SetUpdatedComponent(Mesh);

	InitialLifeSpan = 3.f;

}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &ACBullet::OnHit);
	
}

void ACBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}
