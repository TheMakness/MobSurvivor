// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PermanentUpgradeData.h"
#include "PlayerStatsPUData.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UPlayerStatsPUData : public UPermanentUpgradeData
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual EType GetType() const override
	{
		return Type;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health = 0;

	int DamageBonus = 0;

	int LootMultiplier = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxSpeed = 0;

private:
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EType> Type = EType::PlayerStats;

	
	friend bool operator==(const UPlayerStatsPUData& Lhs, const UPlayerStatsPUData& RHS)
	{
		return static_cast<const UPermanentUpgradeData&>(Lhs) == static_cast<const UPermanentUpgradeData&>(RHS)
			&& Lhs.Health == RHS.Health
			&& Lhs.MaxSpeed == RHS.MaxSpeed;
	}

	friend bool operator!=(const UPlayerStatsPUData& Lhs, const UPlayerStatsPUData& RHS)
	{
		return !(Lhs == RHS);
	}
};
