// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "NormalWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API UNormalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void Appear(int32 AppearSlot,int32 Order);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void Disappear(int32 AppearSlot, int32 Order);
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void Timeout(int32 AppearSlot);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void Finish(int32 AppearSlot);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void Stop();
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void Error();
};
