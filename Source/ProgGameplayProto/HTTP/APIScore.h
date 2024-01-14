#pragma once

#include "CoreMinimal.h"
#include "APIScore.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FAPIScore
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GameType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Email;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumKilledEnemies;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeSurvived;

	FAPIScore() : GameType(0), Email(""), NumKilledEnemies(0), TimeSurvived(0) {}

	FAPIScore(const int GameType, const FString& Username, const int NumKilledEnemies, const float TimeSurvived) : GameType(GameType), Email(Username), NumKilledEnemies(NumKilledEnemies), TimeSurvived(TimeSurvived) {}
};
