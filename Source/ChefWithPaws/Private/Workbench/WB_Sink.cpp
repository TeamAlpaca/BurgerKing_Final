// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "P_Plate.h"
#include "WB_Sink.h"
#include "World/ChefWithPawsCharacter.h"

AWB_Sink::AWB_Sink()
{
	ClassID = TEXT("025");
	SM_Sink_Water = CreateDefaultSubobject<UStaticMeshComponent>("Cleaver");
	SM_Sink_Water->SetVisibility(false);
	SM_Sink_Water->SetMobility(EComponentMobility::Movable);
	SM_Sink_Water->SetupAttachment(Mesh);


}

void AWB_Sink::LoadPickup(APickupBase * const & PickupToLoad)
{
	if ((!CurrentPickup) && PickupToLoad)
	{
		UpdateCurrentPickup(PickupToLoad);
	}
}


void AWB_Sink::UnloadPickup()
{
	UpdateCurrentPickup(nullptr);
}

void AWB_Sink::StartCleaningPlate()
{
	if (CurrentPickup)
	{
		AP_Plate* TempPlate = Cast<AP_Plate>(CurrentPickup);
		if (TempPlate)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sink: Start working."));
			TempPlate->OnBeingCleaned();
			SM_Sink_Water->SetVisibility(true);
			bIsBeingUsed = true;
		}
	}
}

void AWB_Sink::OnStopUsing()
{
	if (CurrentPickup)
	{
		AP_Plate* TempPlate = Cast<AP_Plate>(CurrentPickup);
		if (TempPlate)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sink: Pause working."));
			TempPlate->OnPauseBeingCleaned();
			bIsBeingUsed = false;
		}
	}
}

void AWB_Sink::OnPlateFullyCleaned()
{
	UE_LOG(LogTemp, Warning, TEXT("Sink: Finish Cleaning."));
	if (CurrentPickup)
	{
		CurrentPickup->SetActorLocation(GetActorLocation() + PlateLocationOffset);
		SM_Sink_Water->SetVisibility(false);
		bIsBeingUsed = false;
	}
	if (CurrentCharacter)
	{
		CurrentCharacter->bIsCleaning = false;
	}
}

bool AWB_Sink::IsBeingUsed()
{
	return bIsBeingUsed;
}