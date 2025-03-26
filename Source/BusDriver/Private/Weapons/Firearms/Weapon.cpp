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

		bCanFire = true;
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

void AWeapon::MainAction_Implementation(bool bIsPressed)
{
	bIsFirePressed = bIsPressed;

	if (!bIsPressed)
	{
		HandleFireRateTimer();
	}
	
	// Implement clicking sound later
	if (WeaponData.CurrentAmmo <= 0)
	{
		NoAmmoLeft();
		return;
	}
	
	if (!bCanFire)
		return;
	
	FullAutoFire();
}

void AWeapon::ReloadAction_Implementation()
{
	if (bIsFirePressed)
		return;
	
	WeaponData.CurrentAmmo = WeaponData.MaxAmmo;
	GEngine->AddOnScreenDebugMessage(-1, 0.8f, FColor::Yellow, FString::Printf(TEXT("Reload ammo: %d"), WeaponData.CurrentAmmo));
}

void AWeapon::NoAmmoLeft()
{
	// *CLICK SOUND LOGIC HERE* //
	HandleFireRateTimer();
}

void AWeapon::HandleFireRateTimer()
{
	float RemainingTime = 0.0f;
    
	// Check if the timer is already active
	if (GetWorld()->GetTimerManager().IsTimerActive(FireDelayTimerHandle))
		RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(FireDelayTimerHandle);

	// If there's no remaining time, start a new timer
	if (RemainingTime <= 0.0f)
		RemainingTime = 60.0f / WeaponData.RateOfFire;

	// Restart the timer with the remaining duration
	GetWorld()->GetTimerManager().SetTimer(
		FireDelayTimerHandle,
		this,
		&AWeapon::ResetFire,
		RemainingTime
	);
}

void AWeapon::ResetFire()
{
	bCanFire = true;
}

void AWeapon::SingleFire()
{
	if (WeaponData.CurrentAmmo <= 0)
		return;
	
	FireLogic();
	HandleFireRateTimer();
}

void AWeapon::FullAutoFire()
{
	if (WeaponData.CurrentAmmo <= 0)
		return;
	
	
	FireLogic();
	if (bIsFirePressed)
	{
		// Start firing in full-auto mode
		GetWorld()->GetTimerManager().SetTimer(
			FireDelayTimerHandle,
			this,
			&AWeapon::FullAutoFire,
			60.0f / WeaponData.RateOfFire,
			true // Looping timer
		);
	}
}

void AWeapon::FireLogic()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.8f, FColor::Yellow, TEXT("Pew"));
	--WeaponData.CurrentAmmo;
	GEngine->AddOnScreenDebugMessage(-1, 0.8f, FColor::Yellow, FString::Printf(TEXT("Ammo Left: %d"), WeaponData.CurrentAmmo));

	if (!WeaponMesh) return;

	// Get socket transform
	const FVector MuzzleLocation = WeaponMesh->GetSocketLocation("muzzle");
	const FRotator MuzzleRotation = WeaponMesh->GetSocketRotation("muzzle");

	// Calculate trace start/end points
	const FVector TraceStart = MuzzleLocation;
	const FVector TraceEnd = TraceStart + (MuzzleRotation.Vector() * 1500.f);

	// Setup collision parameters
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner()); // Ignore weapon owner
	TraceParams.bTraceComplex = true; // Optional: trace against complex geometry

	// Perform line trace
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Camera, // Make sure this matches your project's collision channel
		TraceParams
	);

	// Determine debug color
	FColor DebugColor = bHit ? FColor::Green : FColor::Red;
	float DebugDuration = 5.0f;
	float DebugThickness = 2.0f;

	// Draw debug line
	if (bHit)
	{
		DrawDebugLine(
			GetWorld(),
			TraceStart,
			HitResult.ImpactPoint,
			DebugColor,
			false,
			DebugDuration,
			0,
			DebugThickness
		);
	}
	else
	{
		DrawDebugLine(
			GetWorld(),
			TraceStart,
			TraceEnd,
			DebugColor,
			false,
			DebugDuration,
			0,
			DebugThickness
		);
	}

	bCanFire = false;
}


