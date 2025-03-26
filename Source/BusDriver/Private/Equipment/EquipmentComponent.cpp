// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentComponent.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UEquipmentComponent::SetItemInHands(TScriptInterface<IEquippableInterface> NewItemInHands)
{
	ItemInHands = NewItemInHands;
}

TScriptInterface<IEquippableInterface> UEquipmentComponent::GetItemInHands() const
{
	return ItemInHands;
}

