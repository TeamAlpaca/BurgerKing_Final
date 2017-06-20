// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "WB_Griddle.h"
#include "PickupBase.h"
#include "P_Ingredient.h"
#include "P_Food.h"
#include "World/ChefWithPawsCharacter.h"

AWB_Griddle::AWB_Griddle()
{
	ClassID = TEXT("024");
	PickupLocationOffset = FVector(0.0f, 0.0f, 0.0f);
}

void AWB_Griddle::BeginPlay()
{
	Super::BeginPlay();
}

void AWB_Griddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





void AWB_Griddle::LoadPickup(APickupBase * const & PickupToLoad)
{
	if ((!CurrentPickup) && PickupToLoad)
	{
		UpdateCurrentPickup(PickupToLoad);
		StartProcessIngredient();
	}
}

void AWB_Griddle::UnloadPickup()
{
	StopProcessIngredient();
	if (CurrentPickup->getClassID().Contains(TEXT("012")))
	{
		AP_Food* TempFood = Cast<AP_Food>(CurrentPickup);
		if (TempFood && TempFood->IsBeingOvercooked())
		{
			TempFood->OnStopBeingOvercooked();
		}
	}
	UpdateCurrentPickup(nullptr);
}

void AWB_Griddle::StartProcessIngredient()
{
	if (CurrentPickup)
	{
		AP_Ingredient* TempIngredient = Cast<AP_Ingredient>(CurrentPickup);
		if (TempIngredient)
		{
			UE_LOG(LogTemp, Warning, TEXT("ChopBoard: Start working."));
			TempIngredient->OnBeingProcessed();
		}
	}
}

void AWB_Griddle::StopProcessIngredient()
{
	if (CurrentPickup)
	{
		// food and ingredient
		if (CurrentPickup->getClassID().Contains(TEXT("011")))
		{
			AP_Ingredient* TempIngredient = Cast<AP_Ingredient>(CurrentPickup);
			if (TempIngredient)
			{
				TempIngredient->OnPauseBeingProcessed();
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("ChopBoard: Pause working."));
	}
}

void AWB_Griddle::OnIngredientFullyProcessed()
{
	AP_Food* TempFood = Cast<AP_Food>(CurrentPickup);
	if (TempFood)
	{
		TempFood->OnStartBeingOvercooked();
	}
}

void AWB_Griddle::OnFoodFulllyOvercooked()
{
	UE_LOG(LogTemp, Warning, TEXT("ChopBoard: Pause working."));
}



