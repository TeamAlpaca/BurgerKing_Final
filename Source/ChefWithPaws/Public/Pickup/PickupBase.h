// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CWPEntityBase.h"
#include "PickupBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPickupState :uint8
{
	Other				UMETA(Displayname = "Other"),
	WithCharacter		UMETA(Displayname = "WithCharacter"),
	WithCounter			UMETA(Displayname = "WithCounter")
};

UCLASS()
class CHEFWITHPAWS_API APickupBase : public ACWPEntityBase
{
	GENERATED_BODY()
	
public:
	APickupBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintPure, Category = "PickupState")
		EPickupState GetCurrentState() const;
	
	UFUNCTION(BlueprintCallable, Category = "PickupState")
		void SetCurrentState(EPickupState NewState);

	UFUNCTION()
		class AChefWithPawsCharacter* GetCurrentCharacter();

	UFUNCTION()
		void UpdateCurrentCharacter(class AChefWithPawsCharacter* const & NewCurrentCharacter);

	UFUNCTION()
		class AWorkbenchBase* GetCurrentWorkbench();

	UFUNCTION()
		void UpdateCurrentWorkbench(class AWorkbenchBase* const & NewCurrentWorkbench);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ID", meta = (AllowPrivateAccess = "true"))
		EPickupState CurrentState;

	UPROPERTY()
		class AChefWithPawsCharacter* CurrentCharacter;

	UPROPERTY()
		class AWorkbenchBase* CurrentWorkbench;

	void HandleNewState(EPickupState NewState);
};
