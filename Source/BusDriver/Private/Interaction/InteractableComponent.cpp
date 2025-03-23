// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableComponent.h"

#include "Interaction/InteractorComponent.h"

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// Bind functions to delegates
	OnUpdateWidgetInfo.AddDynamic(this, &UInteractableComponent::HandleUpdateWidgetInfo);
	OnHoverUpdated.AddDynamic(this, &UInteractableComponent::HandleSetHoverState);
	OnInteract.AddDynamic(this, &UInteractableComponent::HandleInteract);
}

void UInteractableComponent::HandleUpdateWidgetInfo(UInteractableComponent* Interactable)
{
	// Logic for updating widget info
	UE_LOG(LogTemp, Log, TEXT("Widget Info Updated for: %s"), *GetName());
}

void UInteractableComponent::HandleSetHoverState(bool bIsHovering, UInteractorComponent* HoveringInteractor, UInteractableComponent* Interactable)
{
	UInteractionWidget* TempInteractionWidget = HoveringInteractor->GetInteractionWidget();

	if (!TempInteractionWidget)
		return;
	
	// Logic for hover state changes
	if (bIsHovering)
	{
		TempInteractionWidget->SetVisibility(ESlateVisibility::Visible);
		TempInteractionWidget->SetInteractableText(InteractableText);
	}
	else
	{
		TempInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInteractableComponent::HandleInteract(UInteractorComponent* Interactor, UInteractableComponent* Interactable)
{
	// Logic for handling interactions
	UE_LOG(LogTemp, Log, TEXT("%s interacted with %s"), *Interactor->GetName(), *GetName());
}
