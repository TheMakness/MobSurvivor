// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameLevelData.generated.h"

struct FRangeEnemySpawnRule;
struct FPunctualEnemySpawnRule;
class UBonusData;

/**
 * Store rules and references to other assets that are required to start a level
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UGameLevelData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FPunctualEnemySpawnRule> PunctualSpawnRules;

	UPROPERTY(EditAnywhere)
	TArray<FRangeEnemySpawnRule> RangeSpawnRules;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<UBonusData>> Bonuses;

    // The amount of experience given for each orb of experience
	UPROPERTY(EditAnywhere)
	int GainedExperiencePerOrb;

	//Game Duration in minute - Endless mode if 0
	UPROPERTY(EditAnywhere)
	int GameDuration;

	//The amount of gold win if player survive all game duration
	UPROPERTY(EditAnywhere)
	int GoldBonus;
};
