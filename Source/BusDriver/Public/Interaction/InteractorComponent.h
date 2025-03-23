// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "InteractionWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "InteractorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUSDRIVER_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Used Internally
	bool bDetectionActive = true;
	float TimeSinceLastUpdate = 0.f;
	
public:

	// Toggle's the interaction on/off
	UFUNCTION(BlueprintCallable, Category = "Detection")
	void SetDetectionActive(const bool bNewActive);

private:	

	UPROPERTY()
	UCameraComponent* DetectionCamera;
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	TEnumAsByte<ECollisionChannel> DetectionChannel = ECC_Visibility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float DetectionFrequency = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float DetectionLength = 700.f;

protected:

	// Reference to the hovered interactable
	UPROPERTY()
	UInteractableComponent* HoveringInteractable;
	
private:

	// Used to update the whole interaction
	UFUNCTION()
	void UpdateDetection(float DeltaTime);

	// Called every frame to update the interaction progress
	UFUNCTION()
	void UpdateCurrentInteractable(UInteractableComponent* NewHoveringInteractable);
	
	// Updates the Hovering Interactable
	UFUNCTION()
	void UpdateHoveringInteractable();

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection|Debug")
	bool bDebugMode = false;

private:

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

public:

	FORCEINLINE UInteractionWidget* GetInteractionWidget() const { return InteractionWidget; }

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractionWidget(UInteractionWidget* NewInteractionWidget);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();
	
};
