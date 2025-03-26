// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "InteractableComponent.generated.h"

class UInteractorComponent;

/**
 * 
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class BUSDRIVER_API UInteractableComponent : public UBoxComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHoverUpdated, bool, bIsHovering, UInteractorComponent*, HoveringInteractor, UInteractableComponent*, Interactable);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateWidgetInfo, UInteractorComponent*, HoveringInteractor, UInteractableComponent*, Interactable);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteract, UInteractorComponent*, Interactor, UInteractableComponent*, Interactable);

	UInteractableComponent();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	FText InteractableTooltip;

public:
	// Getter for InteractableTooltip
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FText GetTooltip() const { return InteractableTooltip; }

	// Setter for InteractableTooltip
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetTooltip(const FText& NewTooltip) { InteractableTooltip = NewTooltip; }
	
	// Delegates
	
	UPROPERTY(BlueprintAssignable, Category = "Behaviour")
	FOnUpdateWidgetInfo OnUpdateWidgetInfo;
	UPROPERTY(BlueprintAssignable, Category = "Behaviour")
	FOnHoverUpdated OnHoverUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Behaviour")
	FOnInteract OnInteract;

private:

	// Functions
	UFUNCTION(Category = "Interaction")
	void HandleUpdateWidgetInfo(UInteractorComponent* HoveringInteractor, UInteractableComponent* Interactable);

	UFUNCTION(Category = "Interaction")
	void HandleSetHoverState(bool bIsHovering, UInteractorComponent* HoveringInteractor, UInteractableComponent* Interactable);

	UFUNCTION(Category = "Interaction")
	void HandleInteract(UInteractorComponent* Interactor, UInteractableComponent* Interactable);
};
