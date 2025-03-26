// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActionsInterface.h"
#include "WeaponData.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Stats")
	FWeaponData WeaponData;
	
	// Equipment functions
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void EquipWeapon(USkeletalMeshComponent* ParentMesh, FName SocketName);

	UFUNCTION(BlueprintCallable, Category="Equipment")
	void UnequipWeapon();

	// Fire related functions
private:
	
	//// ACTIONS ////

	// Fire
	virtual void MainAction_Implementation() override;
	// Reload
	virtual void ReloadAction_Implementation() override;
	
	UFUNCTION()
	void Fire();

	// Effects, projectile, linetrace etc.
	UFUNCTION()
	void FireLogic();
	
};
