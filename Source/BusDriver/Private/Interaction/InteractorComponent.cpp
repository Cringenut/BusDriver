// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractorComponent.h"

#include "Interaction/InteractableComponent.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent(): DetectionCamera(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	SetDetectionActive(true);
}


// Called every frame
void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!bDetectionActive)
		return;

	UpdateDetection(DeltaTime);
	
	if (!InteractionWidget)
		return;
	
	UpdateInteraction();
}

void UInteractorComponent::SetDetectionActive(const bool bNewActive)
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!IsValid(Pawn) || !Pawn->IsLocallyControlled())
	{
		bDetectionActive = false;
		
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (!IsValid(PlayerController))
	{
		bDetectionActive = false;
		
		return;
	}

	// Find the Camera Component
	DetectionCamera = Pawn->FindComponentByClass<UCameraComponent>();
	if (!IsValid(DetectionCamera))
	{
		bDetectionActive = false;
		
		return;
	}
	
}

void UInteractorComponent::UpdateDetection(float DeltaTime)
{
	TimeSinceLastUpdate += DeltaTime;
	if (TimeSinceLastUpdate >= DetectionFrequency)
	{
		TimeSinceLastUpdate = 0.f;

		UpdateHoveringInteractable();
	}
}

void UInteractorComponent::UpdateHoveringInteractable()
{
	HoveringInteractable = nullptr;

	if (!DetectionCamera || !GetWorld())
		return;

	const FVector Start = DetectionCamera->GetComponentLocation();
	const FVector Direction = DetectionCamera->GetForwardVector();
	const FVector End = Start + (Direction * DetectionLength);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		DetectionChannel.GetValue(),
		TraceParams
	);

	// Debug Visualization
	if (bDebugMode)
	{
		const FColor TraceColor = bHit ? FColor::Green : FColor::Red;
		const float DebugDuration = DetectionFrequency > 0 ? DetectionFrequency : 0.1f;
        
		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			TraceColor,
			false,
			DebugDuration,
			0,
			2.f // Thickness
		);

		if (bHit)
		{
			DrawDebugPoint(
				GetWorld(),
				HitResult.ImpactPoint,
				10.f, // Size
				FColor::Emerald,
				false,
				DebugDuration
			);
		}
	}

	if (bHit)
	{
		HoveringInteractable = Cast<UInteractableComponent>(HitResult.GetComponent());

		if (HoveringInteractable)
		{
			GEngine->AddOnScreenDebugMessage(-1, DetectionFrequency * 2, FColor::Yellow, TEXT("Hovering"));	
		}
	}
}


void UInteractorComponent::UpdateInteraction()
{
	// MOVE TO INTERACTABLE LATER!!!!!!
	if (HoveringInteractable && InteractionWidget->IsVisible())
	{
		InteractionWidget->SetInteractionText(HoveringInteractable->InteractionText);
	}
	else if (HoveringInteractable && !InteractionWidget->IsVisible())
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		InteractionWidget->SetInteractionText(HoveringInteractable->InteractionText);
	}
	else
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInteractorComponent::SetInteractionWidget(UInteractionWidget* NewInteractionWidget)
{
	InteractionWidget = NewInteractionWidget;
}


