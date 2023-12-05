// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBonusData.h"

#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"

void UWeaponBonusData::ApplyOnMainCharacter()
{
	APlayerCharacter* MainCharacter = UGameUtils::GetMainCharacter();
	if (!IsValid(MainCharacter)) return;

	UWeaponComponent* Weapon = MainCharacter->GetWeapon();
	if (!IsValid(Weapon)) return;

	Apply(MainCharacter, Weapon);
}

void UWeaponBonusData::Apply(APlayerCharacter* Character, UWeaponComponent* Weapon)
{
	ApplyEffects(Character, Weapon);

	Weapon->BonusFireRate += BonusFireRate;
	Weapon->BonusFireRateMultiplier += BonusFireRateMultiplier;
	Weapon->BonusNumberOfShots += BonusNumberOfShots;
	Weapon->BonusNumberOfShotsMultiplier += BonusNumberOfShotsMultiplier;
	Weapon->BonusPrecision += BonusPrecision;
	Weapon->BonusPrecisionMultiplier += BonusPrecisionMultiplier;
	Weapon->BonusSpread += BonusSpread;
	Weapon->BonusSpreadMultiplier += BonusSpreadMultiplier;
	Weapon->BonusDamages += BonusDamages;
	Weapon->BonusDamagesMultiplier += BonusDamagesMultiplier;
	Weapon->BonusProjectileSize += BonusProjectileSize;
	Weapon->BonusProjectileSizeMultiplier += BonusProjectileSizeMultiplier;
	Weapon->BonusRange += BonusRange;
	Weapon->BonusRangeMultiplier += BonusRangeMultiplier;
	Weapon->BonusProjectileSpeed += BonusProjectileSpeed;
	Weapon->BonusProjectileSpeedMultiplier += BonusProjectileSpeedMultiplier;
	Weapon->BonusCriticalHitChance += BonusCriticalHitChance;
	Weapon->BonusCriticalHitChanceMultiplier += BonusCriticalHitChanceMultiplier;
	Weapon->BonusCriticalHitDamageMultiplier += BonusCriticalHitDamageMultiplier;
}

void UWeaponBonusData::ApplyEffects(APlayerCharacter* Character, UWeaponComponent* Weapon)
{
	for (int32 i = 0; i < Effects.Num(); i++)
	{
		UProjectileEffect* Effect = NewObject<UProjectileEffect>(this, Effects[i]);

		Weapon->AddEffect(Effect);
	}
}