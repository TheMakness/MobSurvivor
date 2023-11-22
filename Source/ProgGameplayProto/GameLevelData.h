// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameLevelData.generated.h"

class UBonusData;
struct FRangeEnemySpawnRule;
struct FPunctualEnemySpawnRule;

/**
 *
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
	TArray<UBonusData*> Bonuses;

	// Time-limit duration of the level in minutes
	UPROPERTY(EditAnywhere)
	float Duration;

    // God mode
	UPROPERTY(EditAnywhere)
	bool Invincible = false;

    // The amount of experience given for each orb of experience
	UPROPERTY(EditAnywhere)
	int GainedExperiencePerOrb;

	// Enable the spawn of bosses during the game
	UPROPERTY(EditAnywhere)
	bool SpawnBosses = false;
};
