// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelGameMode.generated.h"

class AUpgradesManager;
class ABonusManager;
class AEnemySpawnerManager;
class UGameLevelData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeforeGameOver);

UCLASS(minimalapi)
class ALevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	ALevelGameMode();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameLevelData* GameLevelData = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AEnemySpawnerManager* EnemySpawnerManager = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ABonusManager* BonusManager = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AUpgradesManager* UpgradesManager = nullptr;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION(BlueprintCallable)
	virtual void StartGame();

	UFUNCTION(BlueprintCallable)
	virtual void ReturnToMainMenu();

	
public:
	UFUNCTION(BlueprintCallable)
	virtual bool IsPaused() const override { return bIsPaused; };

	UFUNCTION(BlueprintCallable)
	virtual bool IsGameOver() const { return bIsGameOver; };

	UFUNCTION(BlueprintCallable)
	virtual void SetGamePaused(bool bIsPaused);

	UFUNCTION(BlueprintCallable)
	virtual void GameOver();

	UFUNCTION(BlueprintCallable)
	virtual void Win();

	UPROPERTY()
	FOnBeforeGameOver OnBeforeGameOver;

private:
	bool bIsPaused;
	bool bIsGameOver;
};