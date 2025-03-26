// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/EquippableInterface.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractableComponent.h"
#include "Weapon.generated.h"

UCLASS()
class BUSDRIVER_API AWeapon : public AActor, public IEquippableInterface
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
	
	// Equipment functions
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void EquipWeapon(USkeletalMeshComponent* ParentMesh, FName SocketName);

	UFUNCTION(BlueprintCallable, Category="Equipment")
	void UnequipWeapon();

};
