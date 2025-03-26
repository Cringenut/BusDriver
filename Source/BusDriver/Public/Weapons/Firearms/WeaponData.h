#pragma once

#include "CoreMinimal.h"
#include "WeaponData.generated.h" 

UENUM(BlueprintType)
enum class EFiremodes : uint8  
{
	Single UMETA(DisplayName = "SINGLE"),   // Single shot mode
	FullAuto UMETA(DisplayName = "FULLAUTO"),  // Full auto mode
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	// Default constructor to initialize properties
	FWeaponData()
		: MaxAmmo(30), CurrentAmmo(30), Damage(25.0f), RateOfFire(600), Range(1000.0f)
	{
		// Add default fire modes to the available array
		AvailableFiremodes.Add(EFiremodes::Single, true);
		AvailableFiremodes.Add(EFiremodes::FullAuto, true);
	}

	// Properties for weapon data

	// Maximum ammo amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Stats|Ammo")
	int MaxAmmo;

	// Current ammo count
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Stats|Ammo")
	int CurrentAmmo;

	// Damage dealt per shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Stats|Firing")
	float Damage;

	// Rate of fire (rounds per minute or shots per second)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Stats|Firing")
	int RateOfFire;

	// Available fire modes for the weapon (<Firemode, isAvailable>)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Stats|Firing")
	TMap<EFiremodes, bool> AvailableFiremodes;

	// Weapon range for hitscan weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Stats|Ballistics")
	float Range;
};
