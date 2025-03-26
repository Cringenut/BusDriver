// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableComponent.h"

#include "Interaction/InteractorComponent.h"

UInteractableComponent::UInteractableComponent()
{
	// Set collision preset to custom
	UPrimitiveComponent::SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UPrimitiveComponent::SetCollisionObjectType(ECC_WorldDynamic);
    
	// Ignore all channels except visibility
	UPrimitiveComponent::SetCollisionResponseToAllChannels(ECR_Ignore);
	UPrimitiveComponent::SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// Bind functions to delegates
	OnUpdateWidgetInfo.AddDynamic(this, &UInteractableComponent::HandleUpdateWidgetInfo);
	OnHoverUpdated.AddDynamic(this, &UInteractableComponent::HandleSetHoverState);
	OnInteract.AddDynamic(this, &UInteractableComponent::HandleInteract);
}


void UInteractableComponent::HandleUpdateWidgetInfo(UInteractorComponent* HoveringInteractor,
	UInteractableComponent* Interactable)
{
	UInteractionWidget* TempInteractionWidget = HoveringInteractor->GetInteractionWidget();

	if (!TempInteractionWidget)
		return;
	
	TempInteractionWidget->SetInteractableText(InteractableTooltip);

	if (HoveringInteractor->bDebugMode)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Interactable widget update"));
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
		TempInteractionWidget->SetInteractableText(InteractableTooltip);
	}
	else
	{
		TempInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInteractableComponent::HandleInteract(UInteractorComponent* Interactor, UInteractableComponent* Interactable)
{
	// Logic for handling interactions
	if (Interactor->bDebugMode)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Interactable interaction"));
}
