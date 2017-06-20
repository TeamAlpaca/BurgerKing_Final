// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "P_Plate.h"
#include "Blueprint/UserWidget.h"
#include "WorkbenchBase.h"
#include "WB_Cashier.h"
#include "WB_Sink.h"

AP_Plate::AP_Plate()
{
	ClassID = TEXT("013");
	PrimaryActorTick.bCanEverTick = true;
}


void AP_Plate::BeginPlay()
{
	Super::BeginPlay();
	
	
}



void AP_Plate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bHasPickup)
	{
		UpdatePickupLocation();
	}
}

APickupBase * AP_Plate::GetCurrentPickup()
{
	return CurrentPickup;
}

//  plate interface
void AP_Plate::LoadObject(APickupBase * const & PickupToLoad)
{
	if (PickupToLoad && (!CurrentPickup))
	{
		CurrentPickup = PickupToLoad;
		UpdatePickupLocation();
		bHasPickup = true;
	}
}

void AP_Plate::UpdatePickupLocation()
{
	if (CurrentPickup)
	{
		CurrentPickup->SetActorLocation(GetPickupLocation());
		CurrentPickup->SetActorRotation(GetActorRotation());
	}
}

FVector AP_Plate::GetPickupLocation()
{
	return GetActorLocation()+PickupLocationOffset;
}

void AP_Plate::UnloadObject()
{
	if (CurrentPickup)
	{
		CurrentPickup->SetCurrentState(EPickupState::WithCounter);
		CurrentPickup = nullptr;
		bHasPickup = false;
	}
}

bool AP_Plate::HasPickup()
{
	return bHasPickup;
}

// pickup end
//////////////////////////////////////////////////////////
// clean

void AP_Plate::ToggleClean(bool bIsClean_New)
{
	
	FRotator OriginalRotation = GetActorRotation();
	if (bIsClean_New)
	{
		Mesh->SetStaticMesh(SM_CleanPlate);
		bIsClean = true;
	}
	else
	{
		Mesh->SetStaticMesh(SM_DirtyPlate);
		bIsClean = false;
	}
	Mesh->SetWorldRotation(OriginalRotation);
}

void AP_Plate::OnBeingCleaned_Implementation()
{
	// set timer or unpausetimer
	if (bIsBeingCleaned)
	{
		UE_LOG(LogTemp, Warning, TEXT("Plate: Now being cleaned."));
		GetWorldTimerManager().UnPauseTimer(CleanTimerHandle);
	}
	else
	{
		bIsBeingCleaned = true;
		GetWorldTimerManager().SetTimer(
			CleanTimerHandle,
			this,
			&AP_Plate::UpdateCleanProgress,
			CleanUpdateTime,
			true);
		UE_LOG(LogTemp, Warning, TEXT("Plate: Now start being cleaned."));
	}
}

void AP_Plate::OnPauseBeingCleaned()
{
	GetWorldTimerManager().PauseTimer(CleanTimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("Plate: Now Pause being cleaned."));
}

void AP_Plate::OnFullyCleaned()
{
	ToggleClean(true);
	bIsBeingCleaned = false;
	GetWorldTimerManager().ClearTimer(CleanTimerHandle);

	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
	}

	if (CurrentWorkbench)
	{
		AWB_Sink* TempSink = Cast<AWB_Sink>(CurrentWorkbench);
		if (TempSink)
		{
			TempSink->OnPlateFullyCleaned();
		}
	}
	// should call sink here
}

float AP_Plate::GetCleanUpdateTime()
{
	return CleanUpdateTime;
}

int32 AP_Plate::GetCleanProgress()
{
	return CleanProgress;
}

void AP_Plate::UpdateCleanProgress()
{
	CleanProgress++;
	if (CleanProgress == 100)
	{
		OnFullyCleaned();
	}
}

bool AP_Plate::IsClean()
{
	return bIsClean;
}

void AP_Plate::OnStartRecycling()
{
	//set timer
	// get invisible
	bIsBeingRecycled = true;
	GetWorldTimerManager().SetTimer(
		RecycleTimerHandle,
		this,
		&AP_Plate::OnFullyRecycled,
		RecycleTime,
		false);
	UE_LOG(LogTemp, Warning, TEXT("Plate: Now start recycling."));
	Mesh->SetVisibility(false);
}

void AP_Plate::OnFullyRecycled()
{
	//clear timer
	//call cashier to handle
	// destroy

	bIsBeingRecycled = false;
	GetWorldTimerManager().ClearTimer(RecycleTimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("Plate: fully recycled."));
	if (CurrentWorkbench)
	{
		AWB_Cashier* TempCashier = Cast<AWB_Cashier>(CurrentWorkbench);
		if (TempCashier)
		{
			TempCashier->SpawnPlate();
		}
	}
	this->RemoveFromRoot();
	Destroy();
}

float AP_Plate::GetRecycleTime()
{
	return RecycleTime;
}

bool AP_Plate::IsBeingRecycled()
{
	return bIsBeingRecycled;
}









