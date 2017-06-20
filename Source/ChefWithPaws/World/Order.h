// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Order.generated.h"

UCLASS()
class CHEFWITHPAWS_API AOrder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	FString SFoodID;
	int32 IType;

	int32 CountdownTime;
	FTimerHandle CountdownTimerHandle;
	int32 NormalCountdownTime;
	int32 ISlot;
public:
	void SetSlot(int32 Slot);
	void CreateNewOrder();
	void AdvanceTimer();
	int32 GetCountdownTime();
	void Finish();
	void Reset();
	void StopCountdown();
	int32 GetType();
	FString GetFoodID();

};
