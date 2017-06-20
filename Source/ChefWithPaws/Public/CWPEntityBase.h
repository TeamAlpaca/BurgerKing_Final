// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CWPEntityBase.generated.h"

UCLASS()
class CHEFWITHPAWS_API ACWPEntityBase : public AActor
{
	GENERATED_BODY()
	// Sets default values for this actor's properties
	
public:	
	ACWPEntityBase();

	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//ID
	UFUNCTION(BlueprintPure, Category = "ID")
		FString getClassID()const;

	UFUNCTION(BlueprintCallable, Category = "ID")
		void setClassID(const FString &NewClassID);
	

	//SM
	UFUNCTION(Blueprintpure,Category="StaticMesh")
		UStaticMeshComponent* getMesh()const;

	
protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="ID", meta = (AllowPrivateAccess = "true"))
		FString ClassID = "";

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="StaticMesh", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;
private:
	

};
