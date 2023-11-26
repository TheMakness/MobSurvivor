#pragma once

#include "CoreMinimal.h"
#include "PermanentUpgradeData.h"
#include "PermanentUpgrade.generated.h"

class UPermanentUpgradeData;

/**
 * Hold a game upgrade static and mutable data
 */
USTRUCT(BlueprintType)
struct FPermanentUpgrade
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPermanentUpgradeData* Data; 

	// Purchase state of the upgrade
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bPurchased = false;

	int CurrentLevel = 1;
};