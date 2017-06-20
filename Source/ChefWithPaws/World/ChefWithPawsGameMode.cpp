// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ChefWithPaws.h"
#include "ChefWithPawsGameMode.h"
#include "ChefWithPawsCharacter.h"
#include "Menu/NormalWidget.h"

#include "OrderList.h"




AChefWithPawsGameMode::AChefWithPawsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	GameStateClass = AOrderList::StaticClass();
	
}

void  AChefWithPawsGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("InitGameState"));
	ChangeMenuWidget(StartingWidgetClass);
	AOrderList* OrderList = Cast<AOrderList>(GetWorld()->GetGameState());
	check(OrderList);
	UGameplayStatics::CreatePlayer(GetWorld(), 0, true);
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

	OrderList->StartGameplayStateMachine();
	SetGameplayState(ENomalGameplayState::EWaiting);
}

int32 AChefWithPawsGameMode::GetCountdownTime() const
{
	return CountdownTime;
}


void AChefWithPawsGameMode::StartNow()
{
	UE_LOG(LogTemp, Error, TEXT("StartNow"));
	
	CountdownTime = GameCountdownTime;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AChefWithPawsGameMode::AdvanceTimer, 1.0f, true);
	SetGameplayState(ENomalGameplayState::EPlaying);

	Coin = 0;
}

void AChefWithPawsGameMode::ReturnToMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "main");
}

void AChefWithPawsGameMode::AdvanceTimer()
{
	if (CountdownTime == GameCountdownTime)
	{
		CreateNewOrder();
		--CountdownTime;
	}
	else
	{
		--CountdownTime;
		if (CountdownTime < 1)
		{
			// 倒计时结束，停止运行定时器。
			GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
			//在定时器结束时按需要执行特殊操作。
			FinishGame();
		}
		else 
		{
			if (CountdownTime >= (GameCountdownTime - 45))
			{
				if (CountdownTime == GameCountdownTime - 20)
				{
					CreateNewOrder();
				}
				if (CountdownTime == GameCountdownTime - 35)
				{
					CreateNewOrder();
				}
				if (CountdownTime == GameCountdownTime - 45)
				{
					CreateNewOrder();
				}
			}
			else if (CountdownTime % 5 == 0)
			{
				CreateNewOrder();
			}
		}
	}
}


void AChefWithPawsGameMode::FinishGame()
{
	UNormalWidget*Widget = Cast<UNormalWidget>(CurrentWidget);
	check(Widget);
	Widget->Stop();
	AOrderList* OrderList = Cast<AOrderList>(GetWorld()->GetGameState());
	check(OrderList);
	OrderList->Stop();
	ChangeMenuWidget(EndingWidgetClass);
	SetGameplayState(ENomalGameplayState::EFinish);
}

void AChefWithPawsGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}




ENomalGameplayState AChefWithPawsGameMode::GetGameplayState() const
{
	return GameplayState;
}

void AChefWithPawsGameMode::SetGameplayState(ENomalGameplayState NewState)
{
	GameplayState = NewState;
}
bool AChefWithPawsGameMode::IsWaiting()
{
	return GameplayState == ENomalGameplayState::EWaiting;
}

bool AChefWithPawsGameMode::IsPlaying()
{
	return GameplayState == ENomalGameplayState::EPlaying;
}

void AChefWithPawsGameMode::CreateNewOrder()
{
	AOrderList* OrderList = Cast<AOrderList>(GetWorld()->GetGameState());
	check(OrderList);
	OrderList->CreateNewOrder();
	UE_LOG(LogTemp, Error, TEXT("Order"));
}

int32 AChefWithPawsGameMode::GetCoin() const
{
	return Coin;
}

void AChefWithPawsGameMode::AddCoin(int32 Number)
{
	Coin = Coin + Number;
}

void AChefWithPawsGameMode::MinusCoin(int32 Number)
{
	Coin = Coin - Number;
}

void  AChefWithPawsGameMode::Return()
{
	UGameplayStatics::OpenLevel(GetWorld(), "main");
}