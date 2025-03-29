// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WeaponStateWidget.generated.h"

class AWeapon;

/**
 * 
 */
UCLASS()
class BUSDRIVER_API UWeaponStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Text elements to display ammo and fire mode
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AmmoTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FiremodeTextBlock;

	// Update the widget
	UFUNCTION(BlueprintCallable, Category="Weapon State")
	void UpdateWeaponState(AWeapon* BoundWeapon);
	
};
