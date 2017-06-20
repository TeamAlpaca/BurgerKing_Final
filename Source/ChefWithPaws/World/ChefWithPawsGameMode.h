// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "ChefWithPawsGameMode.generated.h"

UENUM(BlueprintType)
enum class ENomalGameplayState :uint8
{
	EWaiting UMETA(DisplayName = "Waiting"),
	EPlaying UMETA(DisplayName = "Playing"),
	EPause UMETA(DisplayName = "Pause"),
	EFinish UMETA(DisplayName = "Finish"),
};

UCLASS(minimalapi)
class AChefWithPawsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AChefWithPawsGameMode();
	virtual void BeginPlay() override;

	void FinishGame();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> EndingWidgetClass;
	
	UPROPERTY()
		UUserWidget* CurrentWidget;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintPure, Category = "Coin")
		int32 GetCountdownTime()const;


	void AdvanceTimer();

	UFUNCTION(BlueprintCallable, Category = "Strat")
	void StartNow();

	UFUNCTION(BlueprintCallable, Category = "Quit")
		void ReturnToMenu();

protected:

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Coin", Meta = (BlueprintProtected = "true"))
		int32 CountdownTime;

	FTimerHandle CountdownTimerHandle;

private:
	TSubclassOf<APawn> DefaultPawnClass2;
	ENomalGameplayState GameplayState;

public:

	APlayerController* PlayerController1;
	APlayerController* PlayerController2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GameCountdownTime=240;

	ENomalGameplayState GetGameplayState()const;

	void SetGameplayState(ENomalGameplayState NewState);

	UFUNCTION(BlueprintCallable, Category = "Game State")
		bool IsWaiting();
	UFUNCTION(BlueprintCallable, Category = "Game State")
		bool IsPlaying();

	void CreateNewOrder();

	UFUNCTION(BlueprintPure, Category = "Coin")
		int32 GetCoin()const;

	UFUNCTION(BlueprintCallable, Category = "Coin")
		void AddCoin(int32 Number);

	UFUNCTION(BlueprintCallable, Category = "Coin")
		void MinusCoin(int32 Number);

	UFUNCTION(BlueprintCallable, Category = "Menu")
		void  Return();

	class AOrderList* OrderList;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Coin", Meta = (BlueprintProtected = "true"))
		int32 Coin;
};



