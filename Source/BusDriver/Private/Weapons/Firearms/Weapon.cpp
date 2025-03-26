// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Firearms/Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	InteractableComponent->SetTooltip(FText::FromString(TEXT("Equip")));
	InteractableComponent->SetupAttachment(WeaponMesh);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::EquipWeapon(USkeletalMeshComponent* ParentMesh, FName SocketName)
{
	if (WeaponMesh && ParentMesh)
	{
		// Attach weapon to parent mesh
		WeaponMesh->AttachToComponent(ParentMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

		// Prevent from interaction after equipping
		InteractableComponent->UPrimitiveComponent::SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	}
}

void AWeapon::UnequipWeapon()
{
	if (WeaponMesh)
	{
		// Detach from parent component
		WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}


