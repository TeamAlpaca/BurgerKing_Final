// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "PickupBase.h"

APickupBase::APickupBase()
{
	
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("OverlapAll"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ClassID = TEXT("01");
}


// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(EPickupState::Other);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EPickupState APickupBase::GetCurrentState()const {
	return CurrentState;
}

void APickupBase::SetCurrentState(EPickupState NewState)
{
	CurrentState = NewState;

	HandleNewState(CurrentState);
}

AChefWithPawsCharacter * APickupBase::GetCurrentCharacter()
{
	return CurrentCharacter;
}

void APickupBase::UpdateCurrentCharacter(AChefWithPawsCharacter * const & NewCurrentCharacter)
{
	if (NewCurrentCharacter)
	{
		CurrentCharacter = NewCurrentCharacter;
		CurrentWorkbench = nullptr;
		SetCurrentState(EPickupState::WithCharacter);
	}
	
}

AWorkbenchBase * APickupBase::GetCurrentWorkbench()
{
	return CurrentWorkbench;
}

void APickupBase::UpdateCurrentWorkbench(AWorkbenchBase * const & NewCurrentWorkbench)
{
	if (NewCurrentWorkbench)
	{
		CurrentWorkbench = NewCurrentWorkbench;
		CurrentCharacter = nullptr;
		SetCurrentState(EPickupState::WithCounter);
	}
}

void APickupBase::HandleNewState(EPickupState NewState) {

	switch (NewState) {

		case EPickupState::Other:
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup:set state to Other"));
		}break;

		case EPickupState::WithCharacter: 
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup:set state to WithCharacter"));
		}break;

		case EPickupState::WithCounter: 
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup:set state to WithCounter"));
		}break;
	
	}
}