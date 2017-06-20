// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "P_Food.h"
#include "Blueprint/UserWidget.h"
#include "WorkbenchBase.h"
#include "WB_Griddle.h"
#include "P_Overcooked.h"
AP_Food::AP_Food()
{
	ClassID=TEXT("012");
	FoodInfo=TEXT("0000");
	
}

FString AP_Food::GetFoodInfo()
{
	return FoodInfo;
}

bool AP_Food::CanCombine(FString NewFoodInfo)
{
	for(int16 i=0;i<FoodInfo.Len();++i)
	{
		if(FoodInfo.Mid(i,1)== TEXT("1") && NewFoodInfo.Mid(i,1)== TEXT("1"))
		{
			return false;
		}
	}
	return true;
}
void AP_Food::Combine(FString NewFoodInfo)
{	
	if(CanCombine(NewFoodInfo))
	{
		// set new food info
		FString CombinedFoodInfo;
		for(int16 i=0;i<FoodInfo.Len();++i)
		{
			if(FoodInfo.Mid(i,1)== TEXT("1") || NewFoodInfo.Mid(i,1)== TEXT("1"))
			{
				CombinedFoodInfo.Append(TEXT("1"));
			}
			else
			{
				CombinedFoodInfo.Append(TEXT("0"));
			}
		}
		FoodInfo = CombinedFoodInfo;
		UE_LOG(LogTemp, Warning, TEXT("Food: Combining: %s + %s = %s"), *FoodInfo, *NewFoodInfo, *CombinedFoodInfo);
		// set static mesh
		for(auto &iter : MeshCombination)
		{
			if(CombinedFoodInfo ==iter.Key)
			{
				Mesh->SetStaticMesh(iter.Value);
			}
		}
	}
}

void AP_Food::OnStartBeingOvercooked_Implementation()
{
	bIsBeingOvercooked=true;
	GetWorldTimerManager().SetTimer(
		OvercookedTimerHandle,
		this,
		&AP_Food::UpdateOvercookedProgress,
		OvercookedUpdateTime,
		true);
	UE_LOG(LogTemp, Warning, TEXT("Food:Now Start being overcooked"));
}

void AP_Food::OnStopBeingOvercooked()
{
	bIsBeingOvercooked = false;
	GetWorldTimerManager().ClearTimer(OvercookedTimerHandle);
	OvercookedProgress = 0;
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
	}
}

void AP_Food::UpdateOvercookedProgress()
{
	OvercookedProgress++;
	if (OvercookedProgress == 100)
	{
		OnFullyOvercooked();
	}
}

void AP_Food::OnFullyOvercooked()
{
	OvercookedProgress = false;
	GetWorldTimerManager().ClearTimer(OvercookedTimerHandle);
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
	}
	// spawn an overcooked and update


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		
		AActor* TempActor = World->SpawnActor<AActor>(OvercookedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		AP_Overcooked* TempOvercooked = Cast<AP_Overcooked>(TempActor);
		AWB_Griddle* TempGriddle = Cast<AWB_Griddle>(CurrentWorkbench);

		TempGriddle->UpdateCurrentPickup(TempOvercooked);
		TempGriddle->OnIngredientFullyProcessed();
		
	}
	// destroy 
	Destroy();
}

int32 AP_Food::GetOvercookedProgress()
{
	return OvercookedProgress;
}

bool AP_Food::CanBeOvercooked()
{
	return bCanBeOvercooked;
}

bool AP_Food::IsBeingOvercooked()
{
	return bIsBeingOvercooked;
}
