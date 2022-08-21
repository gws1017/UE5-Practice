// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"
#include "Global.h"
#include "IRifle.h"
#include "CRifle.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	//size2d 함수는 블루프린트에서 VectorLengthXY임
	//이름이 다른건 매번 찾아 확인할것
	Speed = OwnerCharacter->GetVelocity().Size2D();

	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());

	IIRifle* rifle = Cast<IIRifle>(OwnerCharacter);

	if (!!rifle)
	{
		bEquipped = rifle->GetRifle()->GetEquipped();
		bAiming = rifle->GetRifle()->GetAiming();
	}
}
