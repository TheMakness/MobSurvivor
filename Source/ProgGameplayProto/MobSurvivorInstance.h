// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MobSurvivorInstance.generated.h"

struct FPermanentUpgrade;
class UPlayerStatsPUData;
class UWeaponData;
class UPowerPUData;
class UGameLevelData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGoldChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelChange);

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UGameLevelData* GameLevelData;

	UPROPERTY(BlueprintAssignable)
	FOnGoldChange OnGoldChange;

	UPROPERTY(BlueprintAssignable)
	FOnLevelChange OnLevelChange;

	UFUNCTION(BlueprintCallable)
	void AddGold(int NewGold);

	//True if save has been already loaded in this session
	UFUNCTION()
	void SwitchAlreadyLoadState();

	UFUNCTION()
	void SwitchCanLoadState() { bCanLoad = !bCanLoad; }

	void SetUpgrades(const TArray<FPermanentUpgrade>& Array);

	UFUNCTION()
	FORCEINLINE bool IsAlreadyLoaded() const { return bHasAlreadyLoadSave; }

	UFUNCTION()
	FORCEINLINE bool CanLoad() const { return bCanLoad; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetGoldAmount() const { return GoldAmount; }

	
	TObjectPtr<UWeaponData> GetEquippedWeapon() const;
	TObjectPtr<UPowerPUData> GetEquippedPower() const;
	const TArray<TObjectPtr<UPlayerStatsPUData>>& GetEquippedStatsUpgrades() const;
	const TArray<FPermanentUpgrade>& GetUpgrades() const;
		
	void SetEquippedWeapon(const TObjectPtr<UWeaponData>& Weapon);
	void SetEquippedPower(const TObjectPtr<UPowerPUData>& Power);
	void SetEquippedStatsUpgrades(const TArray<TObjectPtr<UPlayerStatsPUData>>& StatsUpgrades);

	
	UFUNCTION(BlueprintCallable)
	void RemoveGold();
	

private:
	int GoldAmount;
	
	TArray<TObjectPtr<UPlayerStatsPUData>> EquippedStatsUpgrades;
	TObjectPtr<UWeaponData> EquippedWeapon;
	TObjectPtr<UPowerPUData> EquippedPower;
	TArray<FPermanentUpgrade> Upgrades;


	bool bHasAlreadyLoadSave = false;
	bool bCanLoad = false;



};
