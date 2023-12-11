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
	TMap<int, float> FireRate = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> FireRateMultiplier = { {1,1} };

	//roudned to nearest integer
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> NumberOfShots = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> NumberOfShotsMultiplier = { {1,1} };

	//1 is 100% precise, 0 can have a variation of direction up to 30 degrees
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> Precision = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> PrecisionMultiplier = { {1,1} };

	//spread in degrees, unclamped
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> Spread = { {1,0} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> SpreadMultiplier = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> Damages = { {1,10} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	TMap<int, float> DamagesMultiplier = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	TMap<int, float> ProjectileSize = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	TMap<int, float> ProjectileSizeMultiplier = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	TMap<int, float> Range = { {1,700} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	TMap<int, float> RangeMultiplier = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	TMap<int, float> ProjectileSpeed = { {1,1000} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	TMap<int, float> ProjectileSpeedMultiplier = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	TMap<int, float> ProjectileStunTime = { {1,0} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	TMap<int, float> ProjectileStunTimeMultiplier = { {1,1} };

	//0 is 0%, 1 is 100%
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	TMap<int, float> CriticalHitChance = { {1,0.025} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	TMap<int, float> CriticalHitChanceMultiplier = { {1,1} };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	TMap<int, float> CriticalHitDamageMultiplier = { {1,2} };

private:
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EType> Type = EType::Weapon;

	friend bool operator==(const UWeaponData& Lhs, const UWeaponData& RHS)
	{
		return static_cast<const UPermanentUpgradeData&>(Lhs) == static_cast<const UPermanentUpgradeData&>(RHS)
			&& Lhs.FireRate[1] == RHS.FireRate[1]
			&& Lhs.FireRateMultiplier[1] == RHS.FireRateMultiplier[1]
			&& Lhs.NumberOfShots[1] == RHS.NumberOfShots[1]
			&& Lhs.NumberOfShotsMultiplier[1] == RHS.NumberOfShotsMultiplier[1]
			&& Lhs.Precision[1] == RHS.Precision[1]
			&& Lhs.PrecisionMultiplier[1] == RHS.PrecisionMultiplier[1]
			&& Lhs.Spread[1] == RHS.Spread[1]
			&& Lhs.SpreadMultiplier[1] == RHS.SpreadMultiplier[1]
			&& Lhs.Damages[1] == RHS.Damages[1]
			&& Lhs.DamagesMultiplier[1] == RHS.DamagesMultiplier[1]
			&& Lhs.ProjectileSize[1] == RHS.ProjectileSize[1]
			&& Lhs.ProjectileSizeMultiplier[1] == RHS.ProjectileSizeMultiplier[1]
			&& Lhs.Range[1] == RHS.Range[1]
			&& Lhs.RangeMultiplier[1] == RHS.RangeMultiplier[1]
			&& Lhs.ProjectileSpeed[1] == RHS.ProjectileSpeed[1]
			&& Lhs.ProjectileSpeedMultiplier[1] == RHS.ProjectileSpeedMultiplier[1]
			&& Lhs.CriticalHitChance[1] == RHS.CriticalHitChance[1]
			&& Lhs.CriticalHitChanceMultiplier[1] == RHS.CriticalHitChanceMultiplier[1]
			&& Lhs.CriticalHitDamageMultiplier[1] == RHS.CriticalHitDamageMultiplier[1];
	}

	friend bool operator!=(const UWeaponData& Lhs, const UWeaponData& RHS)
	{
		return !(Lhs == RHS);
	}
};
