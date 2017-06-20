// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorkbenchBase.h"
#include "WB_Cashier.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AWB_Cashier : public AWorkbenchBase
{
	GENERATED_BODY()
	
	
public:
	AWB_Cashier();

	UFUNCTION()
		void LoadPickup(class APickupBase* const & SpawnPickupToLoad);

	UFUNCTION()
		void UnloadPickup();

	UFUNCTION()
		void AddPlateToQueue();
	UFUNCTION()
		void SpawnPlate();
	
	
protected:

	int32 PlateInQueue;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Pickup", meta = (BlueprintProtected = "true"))
		TSubclassOf<class AP_Plate> PlateClass;
};
