#pragma once

#include "CoreMinimal.h"
#include "APIScore.generated.h"

USTRUCT()
struct FAPIScore
{
	GENERATED_BODY()

	int NumKilledEnemies;
	float TimeSurvived;

	FAPIScore() : NumKilledEnemies(0), TimeSurvived(0) {}

	FAPIScore(const int NumKilledEnemies, const float TimeSurvived) : NumKilledEnemies(NumKilledEnemies), TimeSurvived(TimeSurvived) {}
};
