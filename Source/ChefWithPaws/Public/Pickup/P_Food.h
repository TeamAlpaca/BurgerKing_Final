// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupBase.h"
#include "P_Food.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AP_Food : public APickupBase
{
	GENERATED_BODY()

public:
	AP_Food();

	UFUNCTION()
		FString GetFoodInfo();

	UFUNCTION()
		bool CanCombine(FString NewFoodInfo);

	UFUNCTION()
		void Combine(FString NewFoodInfo);


	UFUNCTION(BlueprintNativeEvent, Category = "Overcooked")
		void OnStartBeingOvercooked();

	UFUNCTION()
		void OnStopBeingOvercooked();

	UFUNCTION()
		void UpdateOvercookedProgress();
	UFUNCTION()
		void OnFullyOvercooked();

	UFUNCTION(BlueprintPure, Category = "Overcooked")
		int32 GetOvercookedProgress();

	UFUNCTION(BlueprintPure, Category = "Overcooked")
		bool CanBeOvercooked();

	UFUNCTION(BlueprintPure, Category = "Overcooked")
		bool IsBeingOvercooked();
protected:

	// combine
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, category = "Food", meta = (AllowPrivateAccess = "true"))
		FString FoodInfo;

	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, category = "Food", meta = (AllowPrivateAccess = "true"))
		TMap<FString, UStaticMesh*>MeshCombination;
	// overcooked
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, category = "Overcooked", meta = (AllowPrivateAccess = "true"))
		bool bCanBeOvercooked = false;

	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, category = "Overcooked", meta = (AllowPrivateAccess = "true"))
		int32 OvercookedProgress = 0;

	UPROPERTY(EditDefaultsOnly, BLueprintReadWrite, category = "Overcooked", meta = (AllowPrivateAccess = "true"))
		float OvercookedUpdateTime = 0.2f;

	UPROPERTY(EditDefaultsOnly, BLueprintReadWrite, category = "Overcooked", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AP_Overcooked>OvercookedClass;

	UPROPERTY(EditDefaultsOnly, BLueprintReadWrite, category = "Overcooked", meta = (AllowPrivateAccess = "true"))
		FVector OvercookedSpawnOffset = FVector(1.0f, 1.0f, 1.0f);

	FTimerHandle OvercookedTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overcooked", Meta = (BlueprintProtected = true))
		TSubclassOf<class UUserWidget>FoodWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overcooked", Meta = (BlueprintProtected = true))
		class UUserWidget* CurrentWidget;

	bool bIsBeingOvercooked=false;


};