// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "MenuGameMode.h"

void  AMenuGameMode::BeginPlay()
{
	;
}
void AMenuGameMode::GoToLevel1()
{

	//GetWorld()->ServerTravel(FString("/Game/Maps/Level_01"));
	UGameplayStatics::OpenLevel(GetWorld(), "Level_01");

}
void AMenuGameMode::GoToLevel2()
{
	//GetWorld()->ServerTravel(FString("/Game/Maps/level2"));
	UGameplayStatics::OpenLevel(GetWorld(), "level2");
}
