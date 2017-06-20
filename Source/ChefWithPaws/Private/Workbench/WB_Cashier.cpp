// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "WB_Cashier.h"
#include "P_Plate.h"
#include "World/OrderList.h"
#include"P_Food.h"


AWB_Cashier::AWB_Cashier()
{
	ClassID = TEXT("026");
	PlateInQueue = 0;
}

void AWB_Cashier::LoadPickup(APickupBase * const & PickupToLoad)
{
	if (PickupToLoad)
	{
		AP_Plate* TempPlate = Cast<AP_Plate>(PickupToLoad);
		if (TempPlate)
		{
			AP_Food* TempFood = Cast<AP_Food>(TempPlate->GetCurrentPickup());
			if (TempFood)
			{
				FString FoodInfo = TempFood->GetFoodInfo();
				TempPlate->UnloadObject();
				TempFood->Destroy();
				TempPlate->OnStartRecycling();
				TempPlate->AddToRoot();
				Cast<AOrderList>(GetWorld()->GetGameState())->CheckFood(FoodInfo);
			}
			
		}
	}
	
}

void AWB_Cashier::UnloadPickup()
{	
	UpdateCurrentPickup(nullptr);
	if (PlateInQueue > 0)
	{
		PlateInQueue--;
		SpawnPlate();
	}
}

void AWB_Cashier::AddPlateToQueue()
{
	if (CurrentPickup)
	{
		PlateInQueue++;
	}
	else
	{
		SpawnPlate();
	}
}

void AWB_Cashier::SpawnPlate()
{
	//spawn a dirty plate
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		AP_Plate* TempPlate = World->SpawnActor<AP_Plate>(PlateClass, GetPickupSetLocation(), GetActorRotation(), SpawnParams);
		if (TempPlate)
		{
			UpdateCurrentPickup(TempPlate);
			TempPlate->SetCurrentState(EPickupState::WithCounter);
			TempPlate->UpdateCurrentWorkbench(this);
			TempPlate->ToggleClean(false);
			UE_LOG(LogTemp, Warning, TEXT("Cashier: plate Spawned."));
		}
	}

}

