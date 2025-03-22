// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUSDRIVER_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();
	
	/** Sets the item currently held */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetItemInHands(TScriptInterface<IEquipmentInterface> NewItemInHands);

	/** Returns the item currently held */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	TScriptInterface<IEquipmentInterface> GetItemInHands() const;

private:
	/** The item currently in hands that implements EquipmentInterface */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TScriptInterface<IEquipmentInterface> ItemInHands;
	
};
