// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorkbenchBase.h"
#include "WB_Sink.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AWB_Sink : public AWorkbenchBase
{
	GENERATED_BODY()
	
public:

	AWB_Sink();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void LoadPickup(APickupBase * const & PickupToLoad);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void UnloadPickup();

	UFUNCTION(BlueprintCallable, Category = "Clean")
		void StartCleaningPlate();

	UFUNCTION()
	virtual void OnStopUsing()override;

	UFUNCTION(BlueprintCallable, Category = "Clean")
		void OnPlateFullyCleaned();
	
	UFUNCTION(BlueprintPure,Category = "Clean")
		bool IsBeingUsed();
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", Meta = (BlueprintProtected = true))
		UStaticMeshComponent* SM_Sink_Water;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clean", Meta = (BlueprintProtected = true))
		FVector PlateLocationOffset;


	bool bIsBeingUsed=false;
};
