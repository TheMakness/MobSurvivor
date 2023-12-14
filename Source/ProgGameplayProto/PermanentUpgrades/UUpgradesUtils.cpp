#include "UUpgradesUtils.h"

int UUpgradesUtils::GetStatLevel(const TMap<int, float>& Map, int UpgradeLevel)
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

int UUpgradesUtils::GetStatLevel(const TMap<int, int>& Map, int UpgradeLevel)
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

int UUpgradesUtils::GetLevelUPStatLevel(const TMap<int, float>& Map, int UpgradeLevel)
{
	int StatLevel = 1;

	if (Map.Contains(UpgradeLevel+1))
	{
		StatLevel = UpgradeLevel+1;
	}
	else
	{
		StatLevel = UpgradeLevel;
	}

	return StatLevel;
}

int UUpgradesUtils::GetLevelUPStatLevel(const TMap<int, int>& Map, int UpgradeLevel)
{
	int StatLevel = 1;

	if (Map.Contains(UpgradeLevel + 1))
	{
		StatLevel = UpgradeLevel + 1;
	}
	else
	{
		StatLevel = UpgradeLevel;
	}

	return StatLevel;
}
