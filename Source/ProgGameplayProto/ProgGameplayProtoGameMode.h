// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProgGameplayProtoGameMode.generated.h"

class ABonusManager;
class AEnemySpawnerManager;
class UGameLevelData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeforeGameOver);

UCLASS(minimalapi)
class AProgGameplayProtoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProgGameplayProtoGameMode();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameLevelData* GameLevelData = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AEnemySpawnerManager* EnemySpawnerManager = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ABonusManager* BonusManager = nullptr;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION(BlueprintCallable)
	virtual void StartGame();

	UFUNCTION(BlueprintCallable)
	virtual void ReturnToMainMenu();

	
public:
	UFUNCTION()
	virtual void GameOver();
	UPROPERTY()
		FOnBeforeGameOver OnBeforeGameOver;
};