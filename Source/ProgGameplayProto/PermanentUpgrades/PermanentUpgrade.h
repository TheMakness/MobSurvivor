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
	//Use to get the current level of one stat base on general current level of upgrade
	static int GetStatLevel(const TMap<int, float>& Map, int UpgradeLevel)
	{
		int StatLevel = 1;

		if (Map.Contains(UpgradeLevel))
		{
			StatLevel = UpgradeLevel;
		}
		else
		{
			for (int i = UpgradeLevel; i < 1; i--)
			{
				if (Map.Contains(UpgradeLevel))
				{
					StatLevel = i;
				}
			}
		}

		return StatLevel;
	}
	static int GetStatLevel(const TMap<int, int>& Map, int UpgradeLevel)
	{
		int StatLevel = 1;

		if (Map.Contains(UpgradeLevel))
		{
			StatLevel = UpgradeLevel;
		}
		else
		{
			for (int i = UpgradeLevel; i < 1; i--)
			{
				if (Map.Contains(UpgradeLevel))
				{
					StatLevel = i;
				}
			}
		}

		return StatLevel;
	}

	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPermanentUpgradeData* Data; 

	// Purchase state of the upgrade
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bPurchased = false;

	// Current level of the upgrade
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int CurrentLevel = 1;


};

