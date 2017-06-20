// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorkbenchBase.h"
#include "WB_BlankCounter.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AWB_BlankCounter : public AWorkbenchBase
{
	GENERATED_BODY()
	
public:
	AWB_BlankCounter();

	virtual void BeginPlay()override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnFetch() override;

	virtual void OnUse() override;

	UFUNCTION()
		void LoadPickup(class APickupBase*  const &PickupToLoad);

	UFUNCTION()
		void UnloadPickup();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitialPickup", Meta = (BlueprintProtected = true))
		TSubclassOf<class APickupBase> InitialPickupClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitialPickup", Meta = (BlueprintProtected = true))
		bool bSpawnInitialPickup = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InitialPickup", Meta = (BlueprintProtected = true))
		FVector SpawnInitialPickupScaleOffset = FVector(1.0f, 1.0f, 1.0f);
};
