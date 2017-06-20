// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorkbenchBase.h"
#include "WB_Storage_Food.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AWB_Storage_Food : public AWorkbenchBase
{
	GENERATED_BODY()
	
public:
	AWB_Storage_Food();

	virtual void BeginPlay()override;

	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void SpawnFood();



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ingredient, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AP_Food>FoodClass;

	
	
};
