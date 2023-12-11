// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProgGameplayProto/PermanentUpgrades/PermanentUpgradeData.h"
#include "WeaponData.generated.h"

class UPermanentUpgradeData;

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UWeaponData : public UPermanentUpgradeData
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual EType GetType() const override
	{
		return Type;
	}
	
	//number of shots / seconds
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float FireRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float FireRateMultiplier = 1;

	//roudned to nearest integer
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float NumberOfShots = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float NumberOfShotsMultiplier = 1;

	//1 is 100% precise, 0 can have a variation of direction up to 30 degrees
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float Precision = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float PrecisionMultiplier = 1;

	//spread in degrees, unclamped
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float SpreadMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float Damages = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float DamagesMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileSizeMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float Range = 700;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float RangeMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileSpeed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileSpeedMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileStunTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileStunTimeMultiplier = 1;

	//0 is 0%, 1 is 100%
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float CriticalHitChance = 0.025f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float CriticalHitChanceMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float CriticalHitDamageMultiplier = 2;

private:
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EType> Type = EType::Weapon;

	friend bool operator==(const UWeaponData& Lhs, const UWeaponData& RHS)
	{
		return static_cast<const UPermanentUpgradeData&>(Lhs) == static_cast<const UPermanentUpgradeData&>(RHS)
			&& Lhs.FireRate == RHS.FireRate
			&& Lhs.FireRateMultiplier == RHS.FireRateMultiplier
			&& Lhs.NumberOfShots == RHS.NumberOfShots
			&& Lhs.NumberOfShotsMultiplier == RHS.NumberOfShotsMultiplier
			&& Lhs.Precision == RHS.Precision
			&& Lhs.PrecisionMultiplier == RHS.PrecisionMultiplier
			&& Lhs.Spread == RHS.Spread
			&& Lhs.SpreadMultiplier == RHS.SpreadMultiplier
			&& Lhs.Damages == RHS.Damages
			&& Lhs.DamagesMultiplier == RHS.DamagesMultiplier
			&& Lhs.ProjectileSize == RHS.ProjectileSize
			&& Lhs.ProjectileSizeMultiplier == RHS.ProjectileSizeMultiplier
			&& Lhs.Range == RHS.Range
			&& Lhs.RangeMultiplier == RHS.RangeMultiplier
			&& Lhs.ProjectileSpeed == RHS.ProjectileSpeed
			&& Lhs.ProjectileSpeedMultiplier == RHS.ProjectileSpeedMultiplier
			&& Lhs.CriticalHitChance == RHS.CriticalHitChance
			&& Lhs.CriticalHitChanceMultiplier == RHS.CriticalHitChanceMultiplier
			&& Lhs.CriticalHitDamageMultiplier == RHS.CriticalHitDamageMultiplier;
	}

	friend bool operator!=(const UWeaponData& Lhs, const UWeaponData& RHS)
	{
		return !(Lhs == RHS);
	}
};
