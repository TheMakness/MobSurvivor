// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorPlayerState.h"

#include "ProgGameplayProto/PermanentUpgrades/EffectPermanentUpgrade.h"
#include "ProgGameplayProto/PermanentUpgrades/WeaponPermanentUpgrade.h"
#include "ProgGameplayProto/Powers/Power.h"

void AMobSurvivorPlayerState::AddStatUpgrade(UEffectPermanentUpgrade* Upgrade)
{
	EnabledStatUpgrades.Add(Upgrade);
}

void AMobSurvivorPlayerState::RemoveStatUpgrade(UEffectPermanentUpgrade* Upgrade)
{
	EnabledStatUpgrades.Remove(Upgrade);
}

void AMobSurvivorPlayerState::SetWeapon(UWeaponData* NewWeapon)
{
	Weapon = NewWeapon;
}

void AMobSurvivorPlayerState::SetPower(const TSubclassOf<APower> NewPower)
{
	Power = NewPower;
}
bool AMobSurvivorPlayerState::IsWeaponEquipped(UWeaponData *WeaponToCheck) const
{
	return Weapon == WeaponToCheck;
}
bool AMobSurvivorPlayerState::IsPowerEquipped(const TSubclassOf<APower> PowerToCheck) const
{
	return Power == PowerToCheck;
}
bool AMobSurvivorPlayerState::IsStatUpgradeEquipped(UEffectPermanentUpgrade* Upgrade) const
{
	return EnabledStatUpgrades.Contains(Upgrade);
}
