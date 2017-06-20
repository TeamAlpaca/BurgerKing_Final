// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupBase.h"
#include "P_Ingredient.generated.h"

/**
 * 
 */


UCLASS()
class CHEFWITHPAWS_API AP_Ingredient : public APickupBase
{
	GENERATED_BODY()
	
public:
	AP_Ingredient();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent,Category="Process")
	void OnBeingProcessed();

	UFUNCTION(BlueprintCallable, Category = "Process")
	void OnPauseBeingProcessed();

	UFUNCTION(BlueprintPure, Category = "Process")
	float GetProcessUpdateTime()const;

	UFUNCTION(BlueprintCallable, Category = "Process")
	void SetProcessUpdateTime(float NewProcessUpdateTime);
	
	UFUNCTION(BlueprintPure, Category = "Process")
	int32 GetProcessProgress()const;

	UFUNCTION(BlueprintCallable, Category = "Process")
	void UpdateProcessProgress();


	UFUNCTION(BlueprintCallable, Category = "Process")
	void HandleNewProcessProgress();

	UFUNCTION(BlueprintCallable, Category = "Process")
	void OnFullyProcessed();

	UFUNCTION(BlueprintPure, Category = "Process")
	bool IsBeingProcessed()const;

	UFUNCTION(BlueprintPure, Category = "Process")
		FString GetProcessID();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HUD",Meta=(BlueprintProtected=true))
	TSubclassOf<class UUserWidget>IngredientWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = true))
	class UUserWidget* CurrentWidget;

	// Process
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process", Meta = (BlueprintProtected = true))
		TArray<UStaticMesh*>ProcessedStaticMesh;

	FTimerHandle ProcessTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process", Meta = (BlueprintProtected = true))
	float ProcessUpdateTime=0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process", Meta = (BlueprintProtected = true))
	int32 ProcessProgress=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process", Meta = (BlueprintProtected = true))
		FString ProcessWorkbenchID;

	bool bIsBeingProcessed=false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food", Meta = (BlueprintProtected = true))
		TSubclassOf<class AP_Food>FoodClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food", Meta = (BlueprintProtected = true))
		FString FoodID;

	
};
