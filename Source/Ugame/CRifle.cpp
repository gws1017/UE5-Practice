#include "CRifle.h"
#include "IRifle.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "Global.h"

#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
//팩토리구조
//스폰한다.

ACRifle* ACRifle::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<ACRifle>(params);
}

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Weapon/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/Character/Montage/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&UnGrabMontage, "AnimMontage'/Game/Character/Montage/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&FireMontage, "AnimMontage'/Game/Character/Montage/Rifle_Fire_Montage.Rifle_Fire_Montage'");
	
	CHelpers::GetAsset<UParticleSystem>(&FlashParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	CHelpers::GetAsset<UParticleSystem>(&EjectParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	CHelpers::GetAsset<UParticleSystem>(&ImpactParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");
	CHelpers::GetAsset<USoundCue>(&FireSoundCue, "SoundCue'/Game/RifleSound/S_RifleShoot_Cue.S_RifleShoot_Cue'");
	CHelpers::GetAsset<UMaterialInstanceConstant>(&DecalMaterial, "MaterialInstanceConstant'/Game/Decal/M_Decal_Inst.M_Decal_Inst'");

	CHelpers::GetClass<ACBullet>(&BulletClass, "Blueprint'/Game/BP_CBullet.BP_CBullet_C'");

}

void ACRifle::Equip()
{
	CheckTrue(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void ACRifle::Begin_Equip()
{
	bEquipped = true;
	//손붙이기
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
	
}

void ACRifle::End_Equip()
{
	bEquipping = false;

}

void ACRifle::UnEquip()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UnGrabMontage);
}

void ACRifle::Begin_UnEquip()
{
	bEquipped = false;
	//등 붙이기
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);

}

void ACRifle::End_UnEquip()
{
	bEquipping = false;
}

void ACRifle::Begin_Aiming()
{
	bAiming = true;
}

void ACRifle::End_Aiming()
{
	bAiming = false;
}

void ACRifle::Begin_Fire()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);
	CheckFalse(bAiming);
	CheckTrue(bFiring);

	Firing();
}

void ACRifle::Firing()
{

	IIRifle* rifle = Cast<IIRifle>(OwnerCharacter);
	CheckNull(rifle);

	FVector start, end, direction;

	rifle->GetLocationAndDirection(start, end, direction);

	OwnerCharacter->PlayAnimMontage(FireMontage);

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	if (!!player)
		player->PlayCameraShake();

	UGameplayStatics::SpawnEmitterAttached(FlashParticle,Mesh, "MuzzleFlash",FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::SpawnEmitterAttached(EjectParticle,Mesh, "EjectBullet",FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::KeepRelativeOffset);

	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation);

	if (!!BulletClass)
		GetWorld()->SpawnActor<ACBullet>(BulletClass, muzzleLocation, direction.Rotation());

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(OwnerCharacter);
	FHitResult hitResult;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params))
	{
		//어딘가에 탄을 솨서 맞은곳은 삼각형으로 되어잇음
		//충돌체의 수직방향이 있다
		//보통 물체의 정면에 있고, 수직벡터를 노멀벡터라고한다
		//Impactnormal은 맞은 충돌체 수직방향
		FRotator rotator = hitResult.ImpactNormal.Rotation();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, rotator, FVector(2));
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), hitResult.Location, rotator, 10.0f);
	}

	//충돌 검사
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!staticMeshActor)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent->BodyInstance.bSimulatePhysics)//충돌한 액터의 메시 컴포넌트가 물리가 켜저있다면
			{
				direction = staticMeshActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
				direction.Normalize();

				meshComponent->AddImpulseAtLocation(direction * meshComponent->GetMass() * 100, OwnerCharacter->GetActorLocation());
				return;
			}

		}
	}
}

void ACRifle::End_Fire()
{
}


void ACRifle::BeginPlay()
{
	Super::BeginPlay();
	

	//오너 구하기
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	//총붙이기
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bAiming);

	IIRifle* rifle = Cast<IIRifle>(OwnerCharacter);
	CheckNull(rifle);

	FVector start, end, direction;

	rifle->GetLocationAndDirection(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 3.0f);

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(OwnerCharacter);
	FHitResult hitResult;

	//충돌 검사
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!staticMeshActor)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent->BodyInstance.bSimulatePhysics)//충돌한 액터의 메시 컴포넌트가 물리가 켜저있다면
			{
				rifle->OnFocus();
				return;
			}

		}
	}
	rifle->OffFocus();

}


