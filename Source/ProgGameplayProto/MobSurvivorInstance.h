// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MobSurvivorInstance.generated.h"

class UPlayerStatsPUData;
class UWeaponData;
class UPowerPUData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGoldChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelChange);

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
	UPROPERTY(BlueprintAssignable)
	FOnGoldChange OnGoldChange;
	UPROPERTY(BlueprintAssignable)
	FOnLevelChange OnLevelChange;
	

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

	
	TObjectPtr<UWeaponData> GetEquipedWeapon() const;
	TObjectPtr<UPowerPUData> GetEquippedPower() const;
	TArray<TObjectPtr<UPlayerStatsPUData>> GetEquippedStatsUpgrades() const;
		
	void SetEquipedWeapon(TObjectPtr<UWeaponData> Weapon);
	void SetEquippedPower(TObjectPtr<UPowerPUData> Power);
	void SetEquippedStatsUpgrades(TArray<TObjectPtr<UPlayerStatsPUData>> StatsUpgrades);

	UFUNCTION(BlueprintCallable)
	void RemoveGold();
private:
	int GoldAmount;

	TArray<TObjectPtr<UPlayerStatsPUData>> EquippedStatsUpgrades;

	TObjectPtr<UWeaponData> EquippedWeapon;

	TObjectPtr<UPowerPUData> EquippedPower;

	bool bHasAlreadyLoadSave = false;


};
