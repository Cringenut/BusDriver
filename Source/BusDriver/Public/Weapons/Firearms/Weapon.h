// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActionsInterface.h"
#include "WeaponDataStruct.h"
#include "WeaponStateWidget.h"
#include "Camera/CameraComponent.h"
#include "Equipment/EquippableInterface.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractableComponent.h"
#include "Weapon.generated.h"

UCLASS()
class BUSDRIVER_API AWeapon : public AActor, public IEquippableInterface, public IWeaponActionsInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UInteractableComponent* InteractableComponent;

	// Weapon Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	FWeaponDataStruct WeaponData;
	
	// Equipment functions
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void EquipWeapon(USkeletalMeshComponent* ParentMesh, FName SocketName);

	UFUNCTION(BlueprintCallable, Category="Equipment")
	void UnequipWeapon();

	// Enum to String
	FString FiremodeToString(EFiremodes Firemode) const;

	// Fire
private:
	
	//// VARIABLES ////

	bool bCanFire;
	bool bIsFirePressed;
	
	//// ACTIONS ////

	// Fire
	virtual void MainAction_Implementation(bool bIsPressed) override;
	// Reload
	virtual void ReloadAction_Implementation() override;
	// Switch firemode
	virtual void SwitchFiremodeAction_Implementation() override;

	//// TIMER HANDLERS

	FTimerHandle FireDelayTimerHandle;
	FTimerHandle BurstFireTimerHandle;
	
	//// FUNCTIONS ////

	// Handling
	void HandleFireRateTimer();
	void ResetFire();

	// Fire types
	void SingleFire();
	void BurstFire(int ShotsLeft);
	void FullAutoFire();
	
	// Effects, projectile, linetrace etc.
	void FireLogic();

	//// AIM DOWN SIGHT ////
private:
	// Player's camera
	UPROPERTY()
	UCameraComponent* ADSCamera;

	// ADS Transform
	UPROPERTY()
	FTransform ADSTransform;

public:
	// Getters and setters
	UFUNCTION(BlueprintCallable, Category = "ADS")
	void SetADSCamera(UCameraComponent* NewADSCamera) { ADSCamera = NewADSCamera; }

	UFUNCTION(BlueprintCallable, Category = "ADS")
	UCameraComponent* GetADSCamera() const { return ADSCamera; }

	// Getters and setters
	UFUNCTION(BlueprintCallable, Category = "ADS")
	void SetADSTransform(const FTransform& NewADSTransform) { ADSTransform = NewADSTransform; }

	UFUNCTION(BlueprintCallable, Category = "ADS")
	FTransform GetADSTransform() const { return ADSTransform; }

	//// WIDGETS ////
	
private:
	UPROPERTY()
	UWeaponStateWidget* WeaponStateWidget;

public:
	UFUNCTION(BlueprintCallable, Category = "ADS")
	void SetWeaponStateWidget(UWeaponStateWidget* NewWeaponStateWidget)
	{
		WeaponStateWidget = NewWeaponStateWidget;
		if (WeaponStateWidget)
		{
			WeaponStateWidget->UpdateWeaponState(this);
			WeaponStateWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
};
