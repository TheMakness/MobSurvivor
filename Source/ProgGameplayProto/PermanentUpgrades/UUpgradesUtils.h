#pragma once

#include "CoreMinimal.h"
#include "UUpgradesUtils.generated.h"

UCLASS()
class UUpgradesUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//Use to get the current level of one stat base on general current level of upgrade
public:
	
	static int GetStatLevel(const TMap<int, float>& Map, int UpgradeLevel);
	static int GetStatLevel(const TMap<int, int>& Map, int UpgradeLevel);

	static int GetLevelUPStatLevel(const TMap<int, float>& Map, int UpgradeLevel);
	static int GetLevelUPStatLevel(const TMap<int, int>& Map, int UpgradeLevel);

	UFUNCTION(BlueprintCallable)
	static int BP_GetStatLevel_F(const TMap<int, float>& Map, int UpgradeLevel) { return GetStatLevel(Map, UpgradeLevel); };

	UFUNCTION(BlueprintCallable)
	static int BP_GetStatLevel_I(const TMap<int, int>& Map, int UpgradeLevel) { return GetStatLevel(Map, UpgradeLevel); };
};

