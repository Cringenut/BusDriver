// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EquipmentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UEquipmentInterface : public UInterface
{
	GENERATED_BODY()
};


class BUSDRIVER_API IEquipmentInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Equip")
	void Equip(ACharacter* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Equip")
	void Unequip(ACharacter* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Equip")
	void Drop(ACharacter* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Actions")
	void MainAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Actions")
	void SecondaryAction();
};
