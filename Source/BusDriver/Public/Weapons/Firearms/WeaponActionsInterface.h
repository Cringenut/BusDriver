// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponActionsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UWeaponActionsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUSDRIVER_API IWeaponActionsInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Actions")
	void ReloadAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Actions")
	void SwitchFiremodeAction();
};
