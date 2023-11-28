// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorInstance.h"


void UMobSurvivorInstance::AddGold(int NewGold)
{
	GoldAmount += NewGold;
	OnGoldChange.Broadcast();
}

void UMobSurvivorInstance::SwitchAreadyLoadState()
{
	bHasAlreadyLoadSave = true;
}

TObjectPtr<UWeaponData> UMobSurvivorInstance::GetEquippedWeapon() const
{
	return EquippedWeapon;
}

TObjectPtr<UPowerPUData> UMobSurvivorInstance::GetEquippedPower() const
{
	return EquippedPower;
}

TArray<TObjectPtr<UPlayerStatsPUData>> UMobSurvivorInstance::GetEquippedStatsUpgrades() const
{
	return EquippedStatsUpgrades;
}

void UMobSurvivorInstance::SetEquipedWeapon(TObjectPtr<UWeaponData> Weapon)
{
	EquippedWeapon = Weapon;
}

void UMobSurvivorInstance::SetEquippedPower(TObjectPtr<UPowerPUData> Power)
{
	EquippedPower = Power;
}

void UMobSurvivorInstance::SetEquippedStatsUpgrades(TArray<TObjectPtr<UPlayerStatsPUData>> StatsUpgrades)
{
	EquippedStatsUpgrades = StatsUpgrades;
}



void UMobSurvivorInstance::RemoveGold()
{
	GoldAmount = 0;
	OnGoldChange.Broadcast();
}
