// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUSDRIVER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TArray<AInventoryItem*> Inventory;

	// Inventory functions
public:
	// Bool to hide item in world if successful
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddToInventory(AInventoryItem* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<AInventoryItem*> GetInventory() const { return Inventory; }
	
};
