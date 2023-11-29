// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorInstance.h"
#include "PermanentUpgrades/PermanentUpgrade.h"
#include "PermanentUpgrades/PlayerStatsPUData.h"
#include "PermanentUpgrades/PowerPUData.h"


void UMobSurvivorInstance::AddGold(int NewGold)
{
	GoldAmount += NewGold;
	OnGoldChange.Broadcast();
}

void UMobSurvivorInstance::SwitchAreadyLoadState()
{
	bHasAlreadyLoadSave = true;
}

void UMobSurvivorInstance::SetUpgrades(const TArray<FPermanentUpgrade>& Array)
{
	Upgrades = Array;
}

TObjectPtr<UWeaponData> UMobSurvivorInstance::GetEquippedWeapon() const
{
	return EquippedWeapon;
}

TObjectPtr<UPowerPUData> UMobSurvivorInstance::GetEquippedPower() const
{
	return EquippedPower;
}

const TArray<TObjectPtr<UPlayerStatsPUData>>& UMobSurvivorInstance::GetEquippedStatsUpgrades() const
{
	return EquippedStatsUpgrades;
}

const TArray<FPermanentUpgrade>& UMobSurvivorInstance::GetUpgrades() const
{
	return Upgrades;
}

void UMobSurvivorInstance::SetEquippedWeapon(const TObjectPtr<UWeaponData>& Weapon)
{
	EquippedWeapon = Weapon;
}

void UMobSurvivorInstance::SetEquippedPower(const TObjectPtr<UPowerPUData>& Power)
{
	EquippedPower = Power;
}

void UMobSurvivorInstance::SetEquippedStatsUpgrades(const TArray<TObjectPtr<UPlayerStatsPUData>>& StatsUpgrades)
{
	EquippedStatsUpgrades = StatsUpgrades;
}



void UMobSurvivorInstance::RemoveGold()
{
	GoldAmount = 0;
	OnGoldChange.Broadcast();
}
