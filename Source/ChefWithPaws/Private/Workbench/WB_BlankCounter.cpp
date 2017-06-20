// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "WB_BlankCounter.h"
#include "PickupBase.h"
#include "World/ChefWithPawsCharacter.h"

AWB_BlankCounter::AWB_BlankCounter() {
	ClassID = TEXT("021");
}

void AWB_BlankCounter::BeginPlay()
{
	Super::BeginPlay();
	if (bSpawnInitialPickup&&InitialPickupClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			CurrentPickup = World->SpawnActor<APickupBase>(InitialPickupClass, GetPickupSetLocation(), GetActorRotation(), SpawnParams);
			if (CurrentPickup)
			{
				CurrentPickup->getMesh()->SetWorldScale3D(SpawnInitialPickupScaleOffset);
				CurrentPickup->SetCurrentState(EPickupState::WithCounter);
				UpdateCurrentPickup(CurrentPickup);
				UE_LOG(LogTemp, Warning, TEXT("BlankCounter: Pickup initailized."));
			}
		}
	}
}

// Called every frame
void AWB_BlankCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AWB_BlankCounter::OnFetch()
{
	Super::OnFetch();
	APickupBase* TempPickup = CurrentCharacter->GetCurrentPickup();
	// Unload pickup
	if((!GetCurrentPickup()) && TempPickup)
	{
		UpdateCurrentPickup(TempPickup);
	}
	//load pickup
	else if(GetCurrentPickup() && (!TempPickup))
	{
		UpdateCurrentPickup(nullptr);
		////////
	}
}

void AWB_BlankCounter::OnUse()
{
	Super::OnUse();
	

}

void AWB_BlankCounter::LoadPickup(APickupBase * const &PickupToLoad)
{
	if ((!GetCurrentPickup()) && PickupToLoad)
	{
		UpdateCurrentPickup(PickupToLoad);
	}
}

void AWB_BlankCounter::UnloadPickup()
{
	UpdateCurrentPickup(nullptr);
}


