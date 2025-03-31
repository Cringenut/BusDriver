// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set inventory size
	Inventory.SetNum(InventoryStruct.Size);
}



bool UInventoryComponent::AddToInventory(AInventoryItem* ItemToAdd)
{
	if (!ItemToAdd)
		return false;

	for (int Index = 0; Index < Inventory.Num(); Index++)
	{
		if (!Inventory[Index])
		{
			Inventory[Index] = ItemToAdd;
			OnItemAdded.Broadcast(Inventory[Index]);
			return true;
		}
	}

	return false;
}

