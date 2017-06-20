// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorkbenchBase.h"
#include "WB_ChopBoard.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AWB_ChopBoard : public AWorkbenchBase
{
	GENERATED_BODY()
	
public:

	AWB_ChopBoard();

	virtual void BeginPlay()override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnStopUsing()override;

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


protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Cleaver", Meta = (BlueprintProtected = true))
		UStaticMeshComponent* SM_Cleaver;

	bool bIsBeingUsed = false;

};
