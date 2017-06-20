// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "WB_Storage.h"
#include "PickupBase.h"
#include "P_Ingredient.h"
#include "World/ChefWithPawsCharacter.h"

AWB_Storage::AWB_Storage() {
	ClassID = TEXT("022");
}

void AWB_Storage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWB_Storage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWB_Storage::SpawnIngredient()
{
	if (IngredientClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			CurrentPickup = World->SpawnActor<AP_Ingredient>(IngredientClass, GetPickupSetLocation(), this->GetActorRotation(), SpawnParams);
			if (CurrentPickup)
			{
				CurrentPickup->SetCurrentState(EPickupState::WithCounter);
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


