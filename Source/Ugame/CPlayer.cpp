#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "CPlayer.h"
#include "CRifle.h"
#include "CAnimInstance.h"
#include "Global.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	/*SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);*/

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer'
	//애니미에션
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	//카메라세팅
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0,60,0);
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstanceConstant* bodyMaterial;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&bodyMaterial, "MaterialInstanceConstant'/Game/Material/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");

	UMaterialInstanceConstant* logoMaterial;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logoMaterial, "MaterialInstanceConstant'/Game/Material/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterial,this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterial,this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);
	
	//총생성
	Rifle = ACRifle::Spawn(GetWorld(), this);
	//OnRiffle(); //총을 잡은채로 시작하고싶을때
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//함수포인터를 사용 시 함수 주소로 명시해줌
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizonLock", this, &ACPlayer::OnHorizonLock);
	PlayerInputComponent->BindAxis("VerticalLock", this, &ACPlayer::OnVerticalLock);
	
	//키액션
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACPlayer::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACPlayer::OffRunning);

	//RifleInput
	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRiffle);

	//Aim
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	//사원수 Quaternion 사용, 짐벌락 같은 추ㅜㄱ이 없어지는걸 막거나 회전 오차를 줄임
	FVector dir = FQuat(rotator).GetForwardVector().GetUnsafeNormal2D();

	AddMovementInput(dir, Axis);

}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector dir = FQuat(rotator).GetRightVector().GetUnsafeNormal2D();

	AddMovementInput(dir, Axis);
}

void ACPlayer::OnHorizonLock(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACPlayer::OnVerticalLock(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACPlayer::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPlayer::OnRiffle()
{
	if (Rifle->GetEquipped())
	{
		Rifle->UnEquip();
		return;
	}

	Rifle->Equip();
}

void ACPlayer::OnAim()
{
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	SpringArm->TargetArmLength = 100;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	Camera->FieldOfView = 40;

	OnZoomIn();
	Rifle->Begin_Aiming();
}

void ACPlayer::OffAim()
{
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector(0, 60, 0);
	Camera->FieldOfView = 90;

	OnZoomOut();
	Rifle->End_Aiming();
}

void ACPlayer::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

