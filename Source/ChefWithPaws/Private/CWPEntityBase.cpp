// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "CWPEntityBase.h"


// Sets default values
ACWPEntityBase::ACWPEntityBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ClassID = TEXT("0");

	//set Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->Mobility= EComponentMobility::Movable;
	RootComponent=Mesh;

}

// Called when the game starts or when spawned
void ACWPEntityBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACWPEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FString ACWPEntityBase::getClassID()const{
	return ClassID;
}

void ACWPEntityBase::setClassID(const FString &NewClassID){
	ClassID = NewClassID;
}

UStaticMeshComponent* ACWPEntityBase::getMesh()const{
	return Mesh;
}