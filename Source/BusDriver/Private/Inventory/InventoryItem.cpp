// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryItem.h"

#include "Interaction/InteractableComponent.h"
#include "Interaction/InteractorComponent.h"
#include "Inventory/InventoryComponent.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Interactable
	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	
}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();

	if (InteractableComponent)
	{
		InteractableComponent->OnInteract.AddDynamic(this, &AInventoryItem::OnInteractHandler);
		InteractableComponent->SetTooltip(FText::FromString(TEXT("Pick Up")));
	}
	
}

void AInventoryItem::OnInteractHandler(UInteractorComponent* Interactor, UInteractableComponent* Interactable)
{
	// Get the Inventory Component from the Interactor's Owner
	UInventoryComponent* InventoryComponent = Interactor->GetOwner()->FindComponentByClass<UInventoryComponent>();

	if (!InventoryComponent)
		return;

	bool Result = InventoryComponent->AddToInventory(this);
	SetActorHiddenInGame(Result);
	SetActorEnableCollision(Result);
	if (Result)
		InteractableComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void AInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

