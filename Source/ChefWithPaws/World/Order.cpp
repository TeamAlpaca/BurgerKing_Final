// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "World/ChefWithPawsGameMode.h"
#include "Menu/NormalWidget.h"
#include "OrderList.h"
#include "Order.h"

// Sets default values
AOrder::AOrder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SFoodID = "0000";
	IType = 0;

	CountdownTime = 0;
	NormalCountdownTime = 80;
}

// Called when the game starts or when spawned
void AOrder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrder::SetSlot(int32 Slot)
{
	ISlot = Slot + 1;
}

void AOrder::CreateNewOrder()
{
	if (IType == 0)
	{
		IType = rand() % 3 + 1;
		if (IType == 1)//bun+patty
		{
			SFoodID = "1001";
		}
		if (IType == 2)//bun+patty+cabbage
		{
			SFoodID = "1101";
		}
		if (IType == 3)//bun+patty+cabbage+tomato
		{
			SFoodID = "1111";
		}
		CountdownTime = NormalCountdownTime;
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AOrder::AdvanceTimer, 1.0f, true);

		AChefWithPawsGameMode* GameMode = GetWorld()->GetAuthGameMode<AChefWithPawsGameMode>();
		check(GameMode);
		UNormalWidget*Widget = Cast<UNormalWidget>(GameMode->CurrentWidget);
		check(Widget);
		Widget->Appear(ISlot, IType);
		UE_LOG(LogTemp, Error, TEXT("Appear"));
	}
}
void AOrder::AdvanceTimer()
{
	--CountdownTime;
	if (CountdownTime <1)
	{
		AChefWithPawsGameMode* GameMode = GetWorld()->GetAuthGameMode<AChefWithPawsGameMode>();
		check(GameMode);
		UNormalWidget*Widget = Cast<UNormalWidget>(GameMode->CurrentWidget);
		check(Widget);
		Widget->Timeout(ISlot);
		GameMode->MinusCoin(10);
		AOrderList* List = Cast<AOrderList>(GetWorld()->GetGameState());
		List->Missed++;
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);

		//重新计时不改变菜单
		CountdownTime = NormalCountdownTime;
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AOrder::AdvanceTimer, 1.0f, true);
	}
}
void AOrder::Finish()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);

	AChefWithPawsGameMode* GameMode = GetWorld()->GetAuthGameMode<AChefWithPawsGameMode>();
	check(GameMode);
	UNormalWidget*Widget = Cast<UNormalWidget>(GameMode->CurrentWidget);
	check(Widget);
	Widget->Finish(ISlot);
	GameMode->AddCoin(20);
	AOrderList* List = Cast<AOrderList>(GetWorld()->GetGameState());
	List->Finished++;
	//延迟重置
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AOrder::Reset, 1.0f, false);
}
void AOrder::Reset()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	AChefWithPawsGameMode* GameMode = GetWorld()->GetAuthGameMode<AChefWithPawsGameMode>();
	check(GameMode);
	UNormalWidget*Widget = Cast<UNormalWidget>(GameMode->CurrentWidget);
	check(Widget);
	Widget->Disappear(ISlot, IType);

	SFoodID = "0000";
	IType = 0;

}
void AOrder::StopCountdown()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
}
int32 AOrder::GetCountdownTime()
{
	return CountdownTime;
}
int32 AOrder::GetType()
{
	return IType;
}
FString AOrder::GetFoodID()
{
	return SFoodID;
}