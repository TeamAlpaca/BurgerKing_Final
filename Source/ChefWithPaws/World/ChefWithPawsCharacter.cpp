// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ChefWithPaws.h"

#include "CWPEntityBase.h"

#include "PickupBase.h"
#include "P_Ingredient.h"
#include "P_Food.h"
#include "P_Plate.h"

#include "WorkBenchBase.h"
#include "WB_BlankCounter.h"
#include "WB_Storage.h"
#include "WB_ChopBoard.h"
#include "WB_Storage_Food.h"
#include "WB_Griddle.h"
#include "WB_Sink.h"
#include "WB_Cashier.h"
#include "ChefWithPawsCharacter.h"


//////////////////////////////////////////////////////////////////////////
// AChefWithPawsCharacter

AChefWithPawsCharacter::AChefWithPawsCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{	
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	
}


void AChefWithPawsCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChefWithPawsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Grab
	if (CurrentPickup)
	{
		UpdatePickupPosition();
	}

	if (AActor* HitActor = GetFirstPhysicalActorInReach().GetActor())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Character:	Object detected by raycast."));
		AWorkbenchBase* HitWorkbench = Cast<AWorkbenchBase>(HitActor);
		if (HitWorkbench)
		{	
			// update if different
			if (CurrentWorkbench)
			{
				if (CurrentWorkbench != HitWorkbench)
				{
					CurrentWorkbench->OnDeactivated();
					UpdateCurrentWorkbench(HitWorkbench);
					HitWorkbench->OnActivated(this);
					UE_LOG(LogTemp,Warning, TEXT("Workbench updated"));
				}
				
			}
			else
			{
				UpdateCurrentWorkbench(HitWorkbench);
				HitWorkbench->OnActivated(this);
				UE_LOG(LogTemp,Warning, TEXT("Workbench updated"));
			}
		}
		else
		{	
			// lose current workbench
			if (CurrentWorkbench)
			{	
				CurrentWorkbench->OnDeactivated();
				UpdateCurrentWorkbench(nullptr);
			}
			
		}
	}
	else
	{
		if (CurrentWorkbench)
		{
			CurrentWorkbench->OnDeactivated();
			UpdateCurrentWorkbench(nullptr);
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Pick up

APickupBase * AChefWithPawsCharacter::GetCurrentPickup() const
{
	return CurrentPickup;
}

void AChefWithPawsCharacter::UpdateCurrentPickup(APickupBase* const &NewCurrentPickup)
{
	if (NewCurrentPickup)
	{
		CurrentPickup = NewCurrentPickup;
		
	}
	else
	{
		CurrentPickup = nullptr;
	}
}

void AChefWithPawsCharacter::UpdatePickupPosition()
{
	if (CurrentPickup)
	{
		CurrentPickup->SetActorLocation(GetPickupLocation(),true);
		CurrentPickup->SetActorRotation(GetActorRotation());
	}
}

FVector AChefWithPawsCharacter::GetPickupLocation()
{
	return this->GetActorLocation() + (this->GetActorRotation().Vector())*100.0f+FVector(0.0f,0.0f,20.0f);
}

// Pick up end
//////////////////////////////////////////////////////////////////////
AWorkbenchBase* AChefWithPawsCharacter::GetCurrentWorkbench()const
{
	return CurrentWorkbench;
}

void AChefWithPawsCharacter::UpdateCurrentWorkbench(class AWorkbenchBase* const &NewCurrentWorkBench) 
{
	if (NewCurrentWorkBench)
	{
		CurrentWorkbench = NewCurrentWorkBench;
		
	}
	else
	{
		CurrentWorkbench = nullptr;
		
	}
}

///////////////////////////////////////////////////////////////////////////
// Raycast

const FHitResult AChefWithPawsCharacter::GetFirstPhysicalActorInReach()
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(TEXT(""), false, this);
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetRaycastStart(),
		GetRaycastEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return HitResult;
}

FVector AChefWithPawsCharacter::GetRaycastStart()
{	
	FVector TempVector(GetActorLocation());
	float ZOffset = 75.0f;
	TempVector.Z -= ZOffset;
	return TempVector;
}

FVector AChefWithPawsCharacter::GetRaycastEnd()
{
	FVector TempVector(GetActorLocation());
	float RaycastReach = 100.0f;
	TempVector += GetActorRotation().Vector()*RaycastReach;
	float ZOffset = 75.0f;
	TempVector.Z -= ZOffset;
	return TempVector;
}

// Raycast end
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Interactive 

void AChefWithPawsCharacter::FetchFromWorkbench()
{
	APickupBase* TempPickup = GetCurrentWorkbench()->GetCurrentPickup();
	if (CurrentWorkbench)
	{
		UpdateCurrentPickup(TempPickup);
		CurrentPickup->UpdateCurrentCharacter(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FetchFromWorkbench failed : no workbench"));
	}
}

void AChefWithPawsCharacter::PutToWorkbench()
{
	CurrentPickup->UpdateCurrentWorkbench(CurrentWorkbench);
	CurrentPickup->UpdateCurrentCharacter(nullptr);
	CurrentPickup = nullptr;
}





// Interactive end
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Input

void AChefWithPawsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	int32 id = ((Cast<APlayerController>(GetController()))->GetLocalPlayer()->GetControllerId());
	if (id == 0)
	{
		PlayerInputComponent->BindAxis("MoveForward_P1", this, &AChefWithPawsCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight_P1", this, &AChefWithPawsCharacter::MoveRight);
		PlayerInputComponent->BindAction("Fetch_P1", IE_Pressed, this, &AChefWithPawsCharacter::Fetch);
		PlayerInputComponent->BindAction("Use_P1", IE_Pressed, this, &AChefWithPawsCharacter::Use);
	}
	else if (id == 1)
	{
PlayerInputComponent->BindAxis("MoveForward_P2", this, &AChefWithPawsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight_P2", this, &AChefWithPawsCharacter::MoveRight);
	PlayerInputComponent->BindAction("Fetch_P2", IE_Pressed, this, &AChefWithPawsCharacter::Fetch);
	PlayerInputComponent->BindAction("Use_P2", IE_Pressed, this, &AChefWithPawsCharacter::Use);
	}
	

}

void AChefWithPawsCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (bIsChopping || bIsCleaning)
		{
			StopUse();
		}
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, 1.5*Value);
	}
	
}

void AChefWithPawsCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{	
		if (bIsChopping||bIsCleaning)
		{
			StopUse();
		}
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, 1.5*Value);
	}
}

void AChefWithPawsCharacter::Fetch_Implementation()
{
	FString WorkbenchID = TEXT("none");
	FString PickupID = TEXT("none");
	FString WorkbenchPickupID = TEXT("none");
	APickupBase* WorkbenchPickup = nullptr;
	//get ID and WorkbenchPickup
	if (CurrentPickup)
	{
		PickupID = CurrentPickup->getClassID();
	}
	if (CurrentWorkbench)
	{	
		WorkbenchPickup = CurrentWorkbench->GetCurrentPickup();
		WorkbenchID = CurrentWorkbench->getClassID();
		if (WorkbenchPickup)
		{
			WorkbenchPickupID = WorkbenchPickup->getClassID();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Fetch Report: workbench : %s, pickup : %s, workbenchpickup : %s"), *WorkbenchID, *PickupID, *WorkbenchPickupID);
	// must have a workbench
	if (!CurrentWorkbench)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fetch error: no workbench"));
	}

	// with food 
	else if (PickupID.Contains(TEXT("012")))
	{	
		AP_Food* TempFood_Character = Cast<AP_Food>(CurrentPickup);
		// with blank counter
		if (WorkbenchID == TEXT("021"))
		{
			AWB_BlankCounter* TempBlankCounter = Cast<AWB_BlankCounter>(CurrentWorkbench);
			

			// combine food
			if (WorkbenchPickupID.Contains(TEXT("012")))
			{
				
				AP_Food* TempFood_Workbench = Cast<AP_Food>(WorkbenchPickup);

				if (TempFood_Character&&TempFood_Workbench)
				{
					// test if can combine
					if (TempFood_Workbench->CanCombine(TempFood_Character->GetFoodInfo()))
					{
						//combine the food on table
						TempFood_Workbench->Combine(TempFood_Character->GetFoodInfo());
						//destroy food with character
						TempFood_Character->Destroy();
						UpdateCurrentPickup(nullptr);
						bIsHoldingPickup = false;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Character: cannot combine food"));
					}
				}
			}

			// blank counter has a plate
			else if (WorkbenchPickupID.Contains(TEXT("013")))
			{
				AP_Plate* TempPlate = Cast<AP_Plate>(WorkbenchPickup);

				// empty plate
				if (!TempPlate->HasPickup())
				{
					TempPlate->LoadObject(CurrentPickup);
					PutToWorkbench();
					bIsHoldingPickup = false;
				}

				// plate with food
				else
				{
					AP_Food* TempFood_Plate = Cast<AP_Food>(TempPlate->GetCurrentPickup());

					if (TempFood_Character&&TempFood_Plate)
					{
						// test if can combine
						if (TempFood_Plate->CanCombine(TempFood_Character->GetFoodInfo()))
						{
							//combine the food on table
							TempFood_Plate->Combine(TempFood_Character->GetFoodInfo());
							//destroy food with character
							TempFood_Character->Destroy();
							UpdateCurrentPickup(nullptr);
							bIsHoldingPickup = false;
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("Character: cannot combine food"));
						}
					}
				}
			}

			// just put
			else if (!WorkbenchPickup)
			{
				TempBlankCounter->LoadPickup(CurrentPickup);
				PutToWorkbench();
				bIsHoldingPickup = false;
			}
				
		}

		//trashcan
		else if (WorkbenchID == TEXT("027"))
		{
			CurrentPickup->Destroy();
			UpdateCurrentPickup(nullptr);
			bIsHoldingPickup = false;
		}

	}
	
	
	// with plate
	else if (PickupID.Contains(TEXT("013")))
	{
		AP_Plate* TempPlate = Cast<AP_Plate>(CurrentPickup);

		// load food / combine food
		// only when clean
		if (TempPlate->IsClean() && WorkbenchPickup && WorkbenchPickupID.Contains(TEXT("012")))
		{	
			// remove overcook progress bar
			AP_Food* TempFood = Cast<AP_Food>(WorkbenchPickup);
			if (TempFood && TempFood->IsBeingOvercooked())
			{
				TempFood->OnStopBeingOvercooked();
			}
			
			// load food to empty plate
			if (!TempPlate->HasPickup())
			{
				TempPlate->LoadObject(WorkbenchPickup);
				WorkbenchPickup->UpdateCurrentCharacter(this);
				CurrentWorkbench->UpdateCurrentPickup(nullptr);
				UE_LOG(LogTemp, Warning, TEXT("Character: load food to empty plate"));

			}
			// combine food
			else
			{
				AP_Food* TempFood_Plate = Cast<AP_Food>(TempPlate->GetCurrentPickup());
				AP_Food* TempFood_Workbench = Cast<AP_Food>(WorkbenchPickup);
				if (TempFood_Plate&&TempFood_Workbench)
				{
					// test if can combine
					if (TempFood_Workbench->CanCombine(TempFood_Plate->GetFoodInfo()))
					{
						//combine the food on plate
						TempFood_Plate->Combine(TempFood_Workbench->GetFoodInfo());
						//destroy food with character
						TempFood_Workbench->Destroy();
						CurrentWorkbench->UpdateCurrentPickup(nullptr);
						UE_LOG(LogTemp, Warning, TEXT("Character: combine food on plate"));
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Character: cannot combine food"));
					}
				}
			}
		}

		// unload plate to blank counter
		else if (!WorkbenchPickup && WorkbenchID.Contains(TEXT("021")))
		{
			AWB_BlankCounter* TempBlankCounter = Cast<AWB_BlankCounter>(CurrentWorkbench);
			TempBlankCounter->LoadPickup(CurrentPickup);
			PutToWorkbench();
			bIsHoldingPickup = false;
		}
		
		
		// sink
		// must be a dirty plate :(
		// sink cant have other dishes u know what i mean
		else if (WorkbenchID.Contains(TEXT("025")) && (!WorkbenchPickup) && (!TempPlate->IsClean()) )
		{
			AWB_Sink* TempSink = Cast<AWB_Sink>(CurrentWorkbench);
			TempSink->LoadPickup(CurrentPickup);
			PutToWorkbench();
			bIsHoldingPickup = false;
		}

		// deliver
		// plate must have food
		else if (WorkbenchID.Contains(TEXT("026")) && TempPlate->HasPickup())
		{
			AWB_Cashier* TempCashier = Cast<AWB_Cashier>(CurrentWorkbench);
			TempCashier->LoadPickup(CurrentPickup);
			PutToWorkbench();
			bIsHoldingPickup = false;
		}

		//trashcan
		else if (WorkbenchID == TEXT("027") && TempPlate->HasPickup())
		{
			APickupBase* TempPickup = TempPlate->GetCurrentPickup();
			TempPlate->UnloadObject();
			TempPickup->Destroy();
		}
	}

	//with ingredient
	else if (PickupID.Contains(TEXT("011")))
	{
		// to griddle / chopboard depending on processID

		// can only when workbench is empty
		if (!WorkbenchPickup)
		{
			AP_Ingredient* TempIngredient = Cast<AP_Ingredient>(CurrentPickup);
			
			//blank counter
			if (WorkbenchID == TEXT("021"))
			{
				AWB_BlankCounter* TempBlankCounter = Cast<AWB_BlankCounter>(CurrentWorkbench);
				TempBlankCounter->LoadPickup(CurrentPickup);
				PutToWorkbench();
				bIsHoldingPickup = false;
			}
			
			// chopboard
			else if (WorkbenchID == TEXT("023") && TempIngredient->GetProcessID() == TEXT("023"))
			{
				AWB_ChopBoard* TempChopboard = Cast<AWB_ChopBoard>(CurrentWorkbench);
				if (TempChopboard)
				{
					TempChopboard->LoadPickup(CurrentPickup);
					PutToWorkbench();
					bIsHoldingPickup = false;
				}
			}

			// griddle
			else if (WorkbenchID == TEXT("024") && TempIngredient->GetProcessID() == TEXT("024"))
			{
				AWB_Griddle* TempGriddle = Cast<AWB_Griddle>(CurrentWorkbench);
				if (TempGriddle)
				{
					TempGriddle->LoadPickup(CurrentPickup);
					PutToWorkbench();
					bIsHoldingPickup = false;
				}
			}

			//trashcan
			else if (WorkbenchID == TEXT("027"))
			{
				CurrentPickup->Destroy();
				UpdateCurrentPickup(nullptr);
				bIsHoldingPickup = false;
			}
		}
		
	}
	// with overcooked
	else if (PickupID.Contains(TEXT("014")))
	{
		// trashcan
		if (WorkbenchID == TEXT("027"))
		{
			CurrentPickup->Destroy();
			UpdateCurrentPickup(nullptr);
			bIsHoldingPickup = false;
		}
	}
	//with barehand
	else if(!CurrentPickup)
	{
		
		// blank counter
		// must have pickup on workbench
		if (WorkbenchID == TEXT("021") && WorkbenchPickup)
		{
			AWB_BlankCounter* TempBlankCounter = Cast<AWB_BlankCounter>(CurrentWorkbench);
			if (TempBlankCounter)
			{
				FetchFromWorkbench();
				TempBlankCounter->UnloadPickup();
				bIsHoldingPickup = true;
			}
		}

		// Storage
		else if (WorkbenchID == TEXT("022") )
		{
			AWB_Storage* TempStorage = Cast<AWB_Storage>(CurrentWorkbench);
			if (TempStorage)
			{
				TempStorage->SpawnIngredient();
				bIsHoldingPickup = true;
			}
		}

		// Storage_food :(
		else if (WorkbenchID == TEXT("0221"))
		{
			AWB_Storage_Food* TempStorage = Cast<AWB_Storage_Food>(CurrentWorkbench);
			if (TempStorage)
			{
				TempStorage->SpawnFood();
				bIsHoldingPickup = true;
			}
		}

		// chopboard
		else if (WorkbenchID == TEXT("023") && WorkbenchPickup)
		{
			AWB_ChopBoard* TempChopboard = Cast<AWB_ChopBoard>(CurrentWorkbench);
			if (TempChopboard)
			{
				FetchFromWorkbench();
				TempChopboard->UnloadPickup();
				StopUse();
				bIsHoldingPickup = true;
			}
		}

		//griddle
		//only take overcooked stuff
		else if (WorkbenchID == TEXT("024") && WorkbenchPickupID == TEXT("014"))
		{
			AWB_Griddle* TempGriddle = Cast<AWB_Griddle>(CurrentWorkbench);
			if (TempGriddle)
			{
				FetchFromWorkbench();
				TempGriddle->UnloadPickup();
				bIsHoldingPickup = true;
			}
		}
			
		//sink
		else if (WorkbenchID == TEXT("025") && WorkbenchPickup)
		{
			AWB_Sink* TempSink = Cast<AWB_Sink>(CurrentWorkbench);
			if (TempSink)
			{
				FetchFromWorkbench();
				TempSink->UnloadPickup();
				StopUse();
				bIsHoldingPickup = true;
			}
		}
		//delivery
		else if (WorkbenchID == TEXT("026") && WorkbenchPickup)
			{
				AWB_Cashier* TempCashier = Cast<AWB_Cashier>(CurrentWorkbench);
				if (TempCashier)
				{
					FetchFromWorkbench();
					TempCashier->UnloadPickup();
					bIsHoldingPickup = true;
				}
			}
		
	}
	
}

void AChefWithPawsCharacter::Use_Implementation()
{
	FString WorkbenchID = TEXT("none");
	FString PickupID = TEXT("none");
	FString WorkbenchPickupID = TEXT("none");
	APickupBase* WorkbenchPickup = nullptr;
	//get ID and WorkbenchPickup
	if (CurrentPickup)
	{
		PickupID = CurrentPickup->getClassID();
	}
	if (CurrentWorkbench)
	{
		WorkbenchPickup = CurrentWorkbench->GetCurrentPickup();
		WorkbenchID = CurrentWorkbench->getClassID();
		if (WorkbenchPickup)
		{
			WorkbenchPickupID = WorkbenchPickup->getClassID();
		}
	}
		
	UE_LOG(LogTemp, Warning, TEXT("Use Report: workbench : %s, pickup : %s, workbenchpickup : %s"), *WorkbenchID, *PickupID, *WorkbenchPickupID);

	// must without pickup
	// must have a workbench
	// except for extinguisher :P
	if ((!CurrentWorkbench) && CurrentPickup)
	{
		UE_LOG(LogTemp, Warning, TEXT("Use error: no workbench"));
	}

	// chopboard
	// must have ingredients on it
	else if (WorkbenchID == TEXT("023") && WorkbenchPickupID.Contains(TEXT("011")) )
	{	
		AWB_ChopBoard* TempChopboard = Cast<AWB_ChopBoard>(CurrentWorkbench);
		if (!bIsChopping)
		{
			TempChopboard->StartProcessIngredient();
			bIsChopping = true;
		}
		else
		{
			StopUse();
		}
	}
		
	//sink
	else if(WorkbenchID == TEXT("025"))
	{
		AWB_Sink* TempSink = Cast<AWB_Sink>(CurrentWorkbench);
		AP_Plate* TempPlate = Cast<AP_Plate>(WorkbenchPickup);

		if (TempPlate && (!TempPlate->IsClean()))
		{
			if (!bIsCleaning)
			{
				TempSink->StartCleaningPlate();
				bIsCleaning = true;
			}
			else
			{
				StopUse();
			}
		}
		
		
	}
}
void AChefWithPawsCharacter::StopUse_Implementation()
{
	bIsChopping = false;
	bIsCleaning = false;
	UE_LOG(LogTemp, Warning, TEXT("Character: Stop Use"));
	if (CurrentWorkbench)
	{
		CurrentWorkbench->OnStopUsing();
	}
}
////////////////////////////////////////////////////////////////////////
//Input End