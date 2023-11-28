// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "PermanentUpgrades/PermanentUpgrade.h"
#include "UpgradesManager.generated.h"

class UPermanentUpgradeDataList;
class UPowerPUData;
class UWeaponData;
class UPlayerStatsPUData;

/**
 * 
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API AUpgradesManager : public AInfo
{
	GENERATED_BODY()
	

public:
	AUpgradesManager();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	const TArray<FPermanentUpgrade>& GetAllUpgrades() const;

	UFUNCTION(BlueprintCallable)
	void BuyUpgrade(UPermanentUpgradeData* UpgradeToBuy);

	UFUNCTION(BlueprintCallable)
	void EquipUpgrade(UPermanentUpgradeData* UpgradeToEquip);

	UFUNCTION(BlueprintCallable)
	bool IsWeaponEquipped(UWeaponData* UpgradeToCheck);
	
	UFUNCTION(BlueprintCallable)
	bool IsPowerEquipped(UPowerPUData* UpgradeToCheck);
	
	UFUNCTION(BlueprintCallable)
	bool IsPlayerStatsEquipped(UPlayerStatsPUData* UpgradeToCheck);

	TArray<TObjectPtr<UPlayerStatsPUData>> GetEquippedStatsUpgrades() const;
	
	TObjectPtr<UWeaponData> GetEquippedWeapon() const;

	TObjectPtr<UPowerPUData> GetEquippedPower() const;

	void LoadUpgradesFromSave(const TArray<FPermanentUpgrade>& Upgrades);

	UFUNCTION(BlueprintCallable)
	void LoadInGameInstance();

	UFUNCTION(BlueprintCallable)
	void LoadFromGameInstance();

private:
	void LoadDefaultUpgrades();
	//Save equiped Upgrade to pass true level

	
	
private:
	// List of all available upgrades in the game. This array MUST be automatically populated
	
	TArray<FPermanentUpgrade> Upgrades;
	

	TArray<TObjectPtr<UPlayerStatsPUData>> EquippedStatsUpgrades;
	
	TObjectPtr<UWeaponData> EquippedWeapon;

	TObjectPtr<UPowerPUData> EquippedPower;

	
	//Data assets that contains list of all upgrades in game.
	UPROPERTY()
	TObjectPtr<UPermanentUpgradeDataList> DefaultsUpgrades;
};