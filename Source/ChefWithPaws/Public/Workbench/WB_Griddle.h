// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorkbenchBase.h"
#include "WB_Griddle.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AWB_Griddle : public AWorkbenchBase
{
	GENERATED_BODY()
	

public:

	AWB_Griddle();

	virtual void BeginPlay()override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void LoadPickup(APickupBase * const & PickupToLoad);

	UFUNCTION()
		void UnloadPickup();

	UFUNCTION()
		void StartProcessIngredient();

	UFUNCTION()
		void StopProcessIngredient();

	UFUNCTION()
		void OnIngredientFullyProcessed();
	
	UFUNCTION()
		void OnFoodFulllyOvercooked();

	
	
	
};
