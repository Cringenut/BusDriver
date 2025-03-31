// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

UCLASS()
class BUSDRIVER_API AInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem();

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UInteractableComponent* InteractableComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handle interaction
	UFUNCTION()
	void OnInteractHandler(UInteractorComponent* Interactor, UInteractableComponent* Interactable);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
