// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "Order.h"

#include "OrderList.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AOrderList : public AGameStateBase
{
	GENERATED_BODY()

protected:
	TArray<AOrder*> List;

public:
	int32 Finished;
	int32 Missed;
	void StartGameplayStateMachine();

	UFUNCTION(BlueprintPure, Category = "CountdownTime")
		int32 GetCountdownTime(int32 i);
	UFUNCTION(BlueprintPure, Category = "Order")
		int32 GetFinished();
	UFUNCTION(BlueprintPure, Category = "Order")
		int32 GetMissed();
	void CreateNewOrder();
	void Stop();
	void CheckFood(FString ID);
	
};
