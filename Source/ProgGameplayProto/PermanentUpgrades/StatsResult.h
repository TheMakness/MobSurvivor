// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatsResult.generated.h"

USTRUCT(Blueprintable)
struct FStatsResult
{
	GENERATED_BODY();

	FStatsResult(FString Info, FString InfoUpdated)
	{
		StatInfo = Info;
		StatInfoUpdated = InfoUpdated;
	}

	FStatsResult()
	{
		StatInfo = "";
		StatInfoUpdated = "";
	}

	UPROPERTY(BlueprintReadWrite)
	FString StatInfo;
	UPROPERTY(BlueprintReadWrite)
	FString StatInfoUpdated;


};
