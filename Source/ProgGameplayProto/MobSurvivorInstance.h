// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MobSurvivorInstance.generated.h"

class UGameLevelData;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorInstance : public 	UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UGameLevelData* DA_Level;
	

	

public:
	UFUNCTION(BlueprintCallable)
	void AddGold(int NewGold);

	//True if save has been already loaded in this session
	UFUNCTION(BlueprintCallable)
	void SwitchAreadyLoadState();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetAlreadyLoad() const { return bHasAlreadyLoadSave; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetGoldAmount() const { return GoldAmount; }
private:
	int GoldAmount;
	bool bHasAlreadyLoadSave = false;
	
};
