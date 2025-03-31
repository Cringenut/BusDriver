// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "InventoryStructs.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent) )
class BUSDRIVER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, AInventoryItem*, AddedItem);

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Weapon Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FInventoryStruct InventoryStruct;
	
private:
	UPROPERTY()
	TArray<AInventoryItem*> Inventory;

	// Inventory functions
public:
	// Event dispatcher for item added
	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnItemAdded OnItemAdded;
	
	// Bool to hide item in world if successful
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddToInventory(AInventoryItem* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<AInventoryItem*> GetInventory() const { return Inventory; }
	
};
