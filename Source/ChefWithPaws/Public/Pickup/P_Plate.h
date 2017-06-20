// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupBase.h"
#include "P_Plate.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AP_Plate : public APickupBase
{
	GENERATED_BODY()
	
public:

	AP_Plate();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//pickup
	UFUNCTION(BlueprintPure, category = "Pickup")
		APickupBase* GetCurrentPickup();

	UFUNCTION(BlueprintCallable, category = "Pickup")
		void LoadObject(APickupBase* const & PickupToLoad);

	UFUNCTION(BlueprintCallable, category = "Pickup")
		void UpdatePickupLocation();

	UFUNCTION()
		FVector GetPickupLocation();

	UFUNCTION(BlueprintCallable, category = "Pickup")
		void UnloadObject();

	UFUNCTION(BlueprintPure, category = "Pickup")
		bool HasPickup();

	// clean
	UFUNCTION(BlueprintCallable, category = "Clean")
		void ToggleClean(bool bIsClean_New);

	UFUNCTION(BlueprintNativeEvent, category = "Clean")
		void OnBeingCleaned();

	UFUNCTION(BlueprintCallable, category = "Clean")
		void OnPauseBeingCleaned();

	UFUNCTION(BlueprintCallable, category = "Clean")
		void OnFullyCleaned();

	UFUNCTION(BlueprintPure, category = "Clean")
		float GetCleanUpdateTime();

	UFUNCTION(BlueprintPure, category = "Clean")
		int32 GetCleanProgress();

	UFUNCTION(BlueprintCallable, category = "Clean")
		void UpdateCleanProgress();

	UFUNCTION(BlueprintPure, category = "Clean")
		bool IsClean();


	// recycle
	UFUNCTION(BlueprintCallable, category = "Recycle")
		void OnStartRecycling();

	UFUNCTION(BlueprintCallable, category = "Recycle")
		void OnFullyRecycled();

	UFUNCTION(BlueprintPure, category = "Recycle")
		float GetRecycleTime();

	UFUNCTION(BlueprintPure, category = "Recycle")
		bool IsBeingRecycled();



protected:
	//pickup
	APickupBase* CurrentPickup;

	bool bHasPickup = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup", Meta = (BlueprintProtected = true))
		FVector PickupLocationOffset;
	
	//clean
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clean", Meta = (BlueprintProtected = true))
		TSubclassOf<class UUserWidget>PlateWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clean", Meta = (BlueprintProtected = true))
		class UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Clean", meta = (AllowPrivateAccess = "true"))
		UStaticMesh* SM_CleanPlate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Clean", meta = (AllowPrivateAccess = "true"))
		UStaticMesh* SM_DirtyPlate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clean", Meta = (BlueprintProtected = true))
		float CleanUpdateTime = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clean", Meta = (BlueprintProtected = true))
		int32 CleanProgress = 0;

	FTimerHandle CleanTimerHandle;

	bool bIsBeingCleaned = false;

	bool bIsClean = true;



	//recycle
	FTimerHandle RecycleTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clean", Meta = (BlueprintProtected = true))
		float RecycleTime = 20.0f;

	bool bIsBeingRecycled;
};
