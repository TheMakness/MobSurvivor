// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusData.h"
#include "Engine/DataAsset.h"
#include "WeaponBonusData.generated.h"

class UProjectileEffect;
class APlayerCharacter;
class UWeaponComponent;

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UWeaponBonusData : public UBonusData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusFireRate = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusFireRateMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusNumberOfShots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusNumberOfShotsMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusPrecision = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusPrecisionMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusSpread = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusSpreadMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusDamages = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusDamagesMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusProjectileSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusProjectileSizeMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusRangeMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusProjectileSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusProjectileSpeedMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusCriticalHitChance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusCriticalHitChanceMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusCriticalHitDamageMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BonusKnockbackForce = 0;

	virtual void ApplyOnMainCharacter() override;

	virtual void Apply(APlayerCharacter* Character, UWeaponComponent* Weapon);

	virtual void ApplyEffects(APlayerCharacter* Character, UWeaponComponent* Weapon);
};
