// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "MenuGameMode.h"

void AMenuGameMode::StartGame()
{
	GetWorld()->ServerTravel(FString("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"));
}
