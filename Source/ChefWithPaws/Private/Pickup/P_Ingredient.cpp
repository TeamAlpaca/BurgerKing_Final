// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "P_Ingredient.h"
#include "Blueprint/UserWidget.h"
#include "P_Food.h"
#include "WorkbenchBase.h"
#include "WB_ChopBoard.h"
#include "WB_Griddle.h"

AP_Ingredient::AP_Ingredient()
{
	ClassID = TEXT("011");
}

void AP_Ingredient::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(
		ProcessTimerHandle,
		this,
		&AP_Ingredient::UpdateProcessProgress,
		ProcessUpdateTime,
		true);
	GetWorldTimerManager().PauseTimer(ProcessTimerHandle);

}

void AP_Ingredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AP_Ingredient::OnBeingProcessed_Implementation()
{	
	UE_LOG(LogTemp, Warning, TEXT("Ingredient: Now being processed."));
	bIsBeingProcessed = true;
	GetWorldTimerManager().UnPauseTimer(ProcessTimerHandle);

}

void AP_Ingredient::OnPauseBeingProcessed()
{
	UE_LOG(LogTemp, Warning, TEXT("Ingredient: Paused being processed."));
	GetWorldTimerManager().PauseTimer(ProcessTimerHandle);
	
}

float AP_Ingredient::GetProcessUpdateTime() const
{
	return ProcessUpdateTime;
}

void AP_Ingredient::SetProcessUpdateTime(float NewProcessUpdateTime)
{
	if (NewProcessUpdateTime <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ingredient: Invalid processupdatetime."));
	}
	else
	{
		ProcessUpdateTime = NewProcessUpdateTime;
	}
}

int32 AP_Ingredient::GetProcessProgress() const
{
	return ProcessProgress;
}

void AP_Ingredient::UpdateProcessProgress()
{

	
	if (ProcessProgress == 100)
	{
		GetWorldTimerManager().ClearTimer(ProcessTimerHandle);
	}
	else
	{
		ProcessProgress++;
	}
	HandleNewProcessProgress();
}

void AP_Ingredient::HandleNewProcessProgress()
{
	FRotator CurrentRotation = Mesh->GetComponentRotation();
	switch (ProcessProgress)
	{
	case 25:
	{
		Mesh->SetStaticMesh(ProcessedStaticMesh[0]);
		Mesh->SetWorldRotation(CurrentRotation);
	}break;
	case 50:
	{
		Mesh->SetStaticMesh(ProcessedStaticMesh[1]);
		Mesh->SetWorldRotation(CurrentRotation);
	}break;
	case 75:
	{
		Mesh->SetStaticMesh(ProcessedStaticMesh[2]);
		Mesh->SetWorldRotation(CurrentRotation);
	}break;
	case 100: 
	{
		UE_LOG(LogTemp, Warning, TEXT("Ingredient: Fully Processed."));
		OnFullyProcessed();
	}break;
		
	}

}

void AP_Ingredient::OnFullyProcessed()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
	}
	
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		FVector OriginalScale = Mesh->GetComponentScale();
		AActor* TempActor = World->SpawnActor<AP_Food>(FoodClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		AP_Food* TempFood = Cast<AP_Food>(TempActor);
		if (TempFood)
		{
			TempFood->SetCurrentState(EPickupState::WithCounter);
			TempFood->UpdateCurrentWorkbench(CurrentWorkbench);
			TempFood->Combine(FoodID);
			TempFood->getMesh()->SetWorldScale3D(OriginalScale);
			CurrentWorkbench->UpdateCurrentPickup(TempFood);
			if (CurrentWorkbench->getClassID().Contains(TEXT("023")))
			{
				AWB_ChopBoard* TempChopboard = Cast<AWB_ChopBoard>(CurrentWorkbench);
				if (TempChopboard)
				{
					TempChopboard->OnIngredientFullyProcessed();
				}
			}
			else if (CurrentWorkbench->getClassID().Contains(TEXT("024")))
			{
				AWB_Griddle* TempGriddle = Cast<AWB_Griddle>(CurrentWorkbench);
				if (TempGriddle)
				{
					TempGriddle->OnIngredientFullyProcessed();
				}
			}
			
			

		}
	}
	Destroy();
}

bool AP_Ingredient::IsBeingProcessed() const
{
	return bIsBeingProcessed;
}

FString AP_Ingredient::GetProcessID()
{
	return ProcessWorkbenchID;
}
