// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "WB_ChopBoard.h"
#include "PickupBase.h"
#include "P_Ingredient.h"
#include "World/ChefWithPawsCharacter.h"

AWB_ChopBoard::AWB_ChopBoard()
{
	ClassID = TEXT("023");
	SM_Cleaver = CreateDefaultSubobject<UStaticMeshComponent>("Cleaver");
	SM_Cleaver->SetVisibility(true);
	SM_Cleaver->SetMobility(EComponentMobility::Movable);
	SM_Cleaver->SetupAttachment(Mesh);

	PickupLocationOffset = FVector(0.0f, 0.0f, 0.0f);
}

void AWB_ChopBoard::BeginPlay()
{
	Super::BeginPlay();
}

void AWB_ChopBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AWB_ChopBoard::OnStopUsing()
{	
	Super::OnStopUsing();
	StopProcessIngredient();
	if (CurrentCharacter)
	{
		CurrentCharacter->bIsChopping = false;
	}
	
}

void AWB_ChopBoard::LoadPickup(APickupBase * const & PickupToLoad)
{
	if ((!CurrentPickup) && PickupToLoad)
	{
		UpdateCurrentPickup(PickupToLoad);
	}
}

void AWB_ChopBoard::UnloadPickup()
{
	
	UpdateCurrentPickup(nullptr);
}

void AWB_ChopBoard::StartProcessIngredient()
{
	if (CurrentPickup)
	{
		AP_Ingredient* TempIngredient = Cast<AP_Ingredient>(CurrentPickup);
		if (TempIngredient)
		{
			UE_LOG(LogTemp, Warning, TEXT("ChopBoard: Start working."));
			SM_Cleaver->SetVisibility(false);
			TempIngredient->OnBeingProcessed();
			bIsBeingUsed = true;
		}
	}
}

void AWB_ChopBoard::StopProcessIngredient()
{
	bIsBeingUsed = false;
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
		SM_Cleaver->SetVisibility(true);
	}
}

void AWB_ChopBoard::OnIngredientFullyProcessed()
{
	bIsBeingUsed = false;
	SM_Cleaver->SetVisibility(true);
	if (CurrentCharacter)
	{
		CurrentCharacter->bIsChopping= false;
	}
}