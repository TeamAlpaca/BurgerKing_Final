// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "WB_Storage_Food.h"
#include "PickupBase.h"
#include "P_Food.h"
#include "World/ChefWithPawsCharacter.h"

AWB_Storage_Food::AWB_Storage_Food() {
	ClassID = TEXT("0221");

}

void AWB_Storage_Food::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWB_Storage_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWB_Storage_Food::SpawnFood()
{
	if (FoodClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			CurrentPickup = World->SpawnActor<AP_Food>(FoodClass, GetPickupSetLocation(), this->GetActorRotation(), SpawnParams);
			if (CurrentPickup)
			{
				CurrentPickup->SetCurrentState(EPickupState::WithCounter);
				AP_Food * TempFood = Cast<AP_Food>(CurrentPickup);
				if (TempFood)
				{
					TempFood->Combine(TEXT("1000"));
				}
				UpdateCurrentPickup(CurrentPickup);
				UE_LOG(LogTemp, Warning, TEXT("WB_Storage: Ingredient Spawned."));
				if (CurrentCharacter && (!CurrentCharacter->GetCurrentPickup()))
				{
					CurrentCharacter->FetchFromWorkbench();
					UpdateCurrentPickup(nullptr);
				}
			}
		}
	}

}



