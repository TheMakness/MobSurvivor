// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PermanentUpgradeData.h"
#include "PlayerStatsPUData.generated.h"

class UPermanentUpgradeComponent_Base;
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
	TMap<int, int> Health {{1, 0}};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, int> DamageBonus = { {1,0} };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, int> LootMultiplier = { {1,0} };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, int> MaxSpeed = { {1,0} };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<UPermanentUpgradeComponent_Base>> ActorComponent;

private:
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EType> Type = EType::PlayerStats;

	
	friend bool operator==(const UPlayerStatsPUData& Lhs, const UPlayerStatsPUData& RHS)
	{
		return static_cast<const UPermanentUpgradeData&>(Lhs) == static_cast<const UPermanentUpgradeData&>(RHS)
			&& Lhs.Health[1] == RHS.Health[1]
			&& Lhs.MaxSpeed[1] == RHS.MaxSpeed[1];
	}

	friend bool operator!=(const UPlayerStatsPUData& Lhs, const UPlayerStatsPUData& RHS)
	{
		return !(Lhs == RHS);
	}
};
