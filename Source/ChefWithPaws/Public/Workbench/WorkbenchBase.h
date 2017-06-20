// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CWPEntityBase.h"
#include "WorkbenchBase.generated.h"

/**
 * 
 */

UCLASS()
class CHEFWITHPAWS_API AWorkbenchBase : public ACWPEntityBase
{
	GENERATED_BODY()

public:

	AWorkbenchBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	void ToggleHighlight(bool bHighlighted);

	// pickup

	class APickupBase* GetCurrentPickup()const;

	void UpdateCurrentPickup(class APickupBase* const &NewPickup);

	bool HasPickup()const;
	
	FVector GetPickupSetLocation()const;

	// pickup end
	UFUNCTION()
		virtual void OnFetch();
	UFUNCTION()
		virtual void OnUse();
	UFUNCTION()
		virtual void OnStopUsing();

	class AChefWithPawsCharacter* GetCurrentCharacter();
	
	void UpdateCurrentCharacter(class AChefWithPawsCharacter* const & NewCharacter);

	UFUNCTION()
		virtual void OnActivated(class AChefWithPawsCharacter* const & OtherCharacter);
	
	UFUNCTION()
		virtual void OnDeactivated();
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		class APickupBase* CurrentPickup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		FVector PickupLocationOffset;
	
	class AChefWithPawsCharacter* CurrentCharacter;

	bool bHasPickup=false;


};
