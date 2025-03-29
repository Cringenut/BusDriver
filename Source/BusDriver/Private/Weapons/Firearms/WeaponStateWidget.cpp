// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Firearms/WeaponStateWidget.h"
#include "Components/TextBlock.h"
#include "Weapons/Firearms/Weapon.h"

void UWeaponStateWidget::UpdateWeaponState(AWeapon* BoundWeapon)
{
	if (!BoundWeapon)
		return;

	FText AmmoText = FText::FromString(FString::Printf(TEXT("%d / %d"), BoundWeapon->WeaponData.CurrentAmmo, BoundWeapon->WeaponData.MaxAmmo));;
	FText FiremodeText = FText::FromString(BoundWeapon->FiremodeToString(BoundWeapon->WeaponData.CurrentFireMode));
	
	AmmoTextBlock->SetText(AmmoText);
	FiremodeTextBlock->SetText(FiremodeText);
}
