// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "ChefWithPawsCharacter.generated.h"


UCLASS(config=Game)
class AChefWithPawsCharacter : public ACharacter
{
	GENERATED_BODY()

	
public:
	AChefWithPawsCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//pickup

	UFUNCTION(BlueprintPure, Category = "Pickup")
		class APickupBase*  GetCurrentPickup()const;
	
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void UpdateCurrentPickup(class APickupBase* const &NewCurrentPickup);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void UpdatePickupPosition();

	UFUNCTION(BlueprintPure, Category = "Pickup")
		FVector GetPickupLocation();


	// end pickup

	//workbench
	UFUNCTION(BlueprintCallable, Category = "Workbench")
		class AWorkbenchBase* GetCurrentWorkbench()const;

	UFUNCTION(BlueprintCallable, Category = "Workbench")
		void UpdateCurrentWorkbench(class AWorkbenchBase* const &NewCurrentWorkBench);

	// end workbench

	// ray cast
	UFUNCTION(BlueprintCallable, Category = "Raycast")
		const FHitResult GetFirstPhysicalActorInReach();

	UFUNCTION(BlueprintCallable, Category = "Raycast")
		FVector GetRaycastStart();

	UFUNCTION(BlueprintCallable, Category = "Raycast")
		FVector GetRaycastEnd();
	//ray cast end

	// interactive
	UFUNCTION()
		void FetchFromWorkbench();

	UFUNCTION()
		void PutToWorkbench();



	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="State")
		bool bIsHoldingPickup = false;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "State")
		bool bIsChopping = false;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "State")
		bool bIsCleaning = false;
 protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	//input

	void MoveForward(float Value);

	void MoveRight(float Value);

	UFUNCTION(BlueprintNativeEvent, Category = "Character Action")
	void Fetch();
	UFUNCTION(BlueprintNativeEvent, Category = "Character Action")
	void Use();
	//end input
	UFUNCTION(BlueprintNativeEvent, Category = "Character Action")
	void StopUse();
		
	UPROPERTY(VisibleAnyWhere, BLueprintReadOnly, category = "Pickup", meta = (AllowPrivateAccess = "true"))
		class APickupBase* CurrentPickup;

	UPROPERTY(VisibleAnyWhere, BLueprintReadOnly, category = "Pickup", meta = (AllowPrivateAccess = "true"))
		class AWorkbenchBase* CurrentWorkbench;

};

