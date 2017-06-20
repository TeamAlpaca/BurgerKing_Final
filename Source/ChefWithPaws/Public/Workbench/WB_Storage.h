// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorkbenchBase.h"
#include "WB_Storage.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AWB_Storage : public AWorkbenchBase
{
	GENERATED_BODY()
	
public:
	AWB_Storage();

	virtual void BeginPlay()override;

	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void SpawnIngredient();



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ingredient, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AP_Ingredient>IngredientClass;

	
};
