// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "World/ChefWithPawsGameMode.h"
#include "Menu/NormalWidget.h"
#include "OrderList.h"



void AOrderList::StartGameplayStateMachine()
{
	for (int32 i = 0; i != 5; i++)
	{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	List.Emplace( GetWorld()->SpawnActor<AOrder>(SpawnInfo));
	List[i]->SetSlot(i);
	UE_LOG(LogTemp, Error, TEXT("set order"));
	}
	Finished = 0;
	Missed = 0;
	
}

void AOrderList::CreateNewOrder()
{
	UE_LOG(LogTemp, Error, TEXT("Create"));
	for (int32 i = 0; i < List.Num(); i++)
	{
		if (List[i]->GetType() == 0)
		{

			List[i]->CreateNewOrder();
			break;
		}
	}
}
void AOrderList::Stop()
{
	for (auto val : List)
	{
		if (val->GetType())
		{
			val->StopCountdown();
		}
	}
}
void AOrderList::CheckFood(FString ID)
{
	bool checkID=false;
	for (auto val : List)
	{
		if (ID == val->GetFoodID())
		{
			val->Finish();
			checkID = true;
			break;
		}
	}
	if (!checkID)
	{
AChefWithPawsGameMode* GameMode = GetWorld()->GetAuthGameMode<AChefWithPawsGameMode>();
	check(GameMode);
	UNormalWidget*Widget = Cast<UNormalWidget>(GameMode->CurrentWidget);
	check(Widget);
	Widget->Error();
	}
	
}

int32 AOrderList::GetMissed()
{
	return Missed;
}

int32 AOrderList::GetCountdownTime(int32 i)
{
	return List[i]->GetCountdownTime();
}

int32 AOrderList::GetFinished()
{
	return Finished;
}