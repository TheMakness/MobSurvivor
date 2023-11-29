// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProgGameplayProtoGameState.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerFinish);

UCLASS()
class PROGGAMEPLAYPROTO_API AProgGameplayProtoGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AProgGameplayProtoGameState();

	UPROPERTY()
	FOnTimerFinish OnTimerFinish;

	virtual void BeginPlay() override;

protected:
	float GameTime = 0;

	float GameTargetDuration = 60;
	float BonusGold = 200;

	bool bHasGameStarted = false;

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetGameTime() const { return GameTime; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetRemainingTime() const { return GameTargetDuration - GameTime; }

	FORCEINLINE float GetBonusGold() const { return BonusGold; }

	void SetGameStarted(bool HasGameStarted);
};