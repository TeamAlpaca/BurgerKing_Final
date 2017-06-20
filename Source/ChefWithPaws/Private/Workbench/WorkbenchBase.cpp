// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "WorkbenchBase.h"
#include "PickupBase.h"
#include "World/ChefWithPawsCharacter.h"

AWorkbenchBase::AWorkbenchBase()
{
	Mesh->SetSimulatePhysics(false);
	Mesh->bGenerateOverlapEvents = false;
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	RootComponent = Mesh;

	ClassID = TEXT("02");

	PickupLocationOffset = FVector(0.0f, 0.0f, 70.0f);
}

void AWorkbenchBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorkbenchBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorkbenchBase::ToggleHighlight(bool bHighLighted)
{
	Mesh->SetRenderCustomDepth(bHighLighted);
}

class APickupBase* AWorkbenchBase::GetCurrentPickup()const {
	return CurrentPickup;
}

void AWorkbenchBase::UpdateCurrentPickup(class APickupBase* const &NewPickup)
{
	if (NewPickup)
	{
		CurrentPickup = NewPickup;
		bHasPickup = true;
		NewPickup->SetActorLocation(GetPickupSetLocation());
		UE_LOG(LogTemp, Warning, TEXT("Workbench: pickup updated."));
	}
	else
	{
		CurrentPickup = nullptr;
		bHasPickup = false;
		UE_LOG(LogTemp, Warning, TEXT("Workbench: pickup lost."));
	}
}

bool AWorkbenchBase::HasPickup()const
{
	return bHasPickup;
}

FVector AWorkbenchBase::GetPickupSetLocation()const
{;
	return PickupLocationOffset + this->GetActorLocation();
}

void AWorkbenchBase::OnFetch()
{
	//UE_LOG(LogTemp, Warning, TEXT("Workbench: OnFetch Called."));

}

void AWorkbenchBase::OnUse()
{
	//UE_LOG(LogTemp, Warning, TEXT("Workbench: OnUse Called."));

}

void AWorkbenchBase::OnStopUsing()
{
	//UE_LOG(LogTemp, Warning, TEXT("Workbench: OnUse Called."));
}

AChefWithPawsCharacter* AWorkbenchBase::GetCurrentCharacter()
{
	return CurrentCharacter;
}

void AWorkbenchBase::UpdateCurrentCharacter(class AChefWithPawsCharacter* const & NewCharacter)
{
	if(NewCharacter)
	{
		CurrentCharacter=NewCharacter;
	}
	else
	{
		CurrentCharacter=nullptr;
	}
}

void AWorkbenchBase::OnActivated(class AChefWithPawsCharacter* const & OtherCharacter)
{
		ToggleHighlight(true);
		UpdateCurrentCharacter(OtherCharacter);
}

void AWorkbenchBase::OnDeactivated()
{
		ToggleHighlight(false);
		UpdateCurrentCharacter(nullptr);
}


