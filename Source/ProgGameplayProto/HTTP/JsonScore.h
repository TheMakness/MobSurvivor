#pragma once

#include "CoreMinimal.h"
#include "JsonScore.generated.h"

USTRUCT()
struct FJsonScore
{
	GENERATED_BODY()

	FJsonScore()
	{
		token = "";
		score = 0;
	}

	FJsonScore(FString token, int score)
	{
		this->token = token;
		this->score = score;
	}

	UPROPERTY()
	FString token;
	UPROPERTY()
	int score;

};

