#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRifle.generated.h"

UCLASS()
class UGAME_API ACRifle : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		FName HandSocket = "Hand_Rifle";
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		FName HolsterSocket = "Holster_Rifle";

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UAnimMontage* GrabMontage;
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UAnimMontage* UnGrabMontage;

public:
	static ACRifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	FORCEINLINE bool GetEquipped() { return bEquipped; }

public:	

	ACRifle();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void UnEquip();
	void Begin_UnEquip();
	void End_UnEquip();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

private:
	class ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
};
