// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractorComponent.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
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

}


// Called every frame
void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!bDetectionActive)
		return;

	UpdateDetection(DeltaTime);
	UpdateInteraction(DeltaTime);
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
}

void UInteractorComponent::UpdateDetection(float DeltaTime)
{
	TimeSinceLastUpdate += DeltaTime;
	if (TimeSinceLastUpdate >= DetectionFrequency)
	{
		TimeSinceLastUpdate = 0.f;
		
	}
}

void UInteractorComponent::UpdateInteraction(float DeltaTime)
{
}

