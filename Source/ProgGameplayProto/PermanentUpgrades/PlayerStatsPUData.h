// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PermanentUpgradeData.h"
#include "UUpgradesUtils.h"
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

	virtual TArray<FStatsResult> GetUpdatedStatsStrings(int CurrentLevel) override
	{

		TArray<FStatsResult> output;
		int StatLevel;

		FString Value0 = TEXT("Heart : " + FString::SanitizeFloat(Health[UUpgradesUtils::GetStatLevel(Health, CurrentLevel)]/2));
		FString Value0_Updated = "";
		StatLevel = UUpgradesUtils::GetLevelUPStatLevel(Health, CurrentLevel);
		if (StatLevel > CurrentLevel)
			Value0_Updated = (TEXT(" -> " + FString::SanitizeFloat(Health[StatLevel] / 2)));

		FString Value1 = TEXT("Damage Bonus : " + FString::SanitizeFloat(DamageBonus[UUpgradesUtils::GetStatLevel(DamageBonus, CurrentLevel)]));
		FString Value1_Updated = "";
		StatLevel = UUpgradesUtils::GetLevelUPStatLevel(DamageBonus, CurrentLevel);
		if (StatLevel > CurrentLevel)
			Value1_Updated = (TEXT(" -> " + FString::SanitizeFloat(DamageBonus[StatLevel])));

		FString Value2 = TEXT("Loot Multiplier : " + FString::SanitizeFloat(LootMultiplier[UUpgradesUtils::GetStatLevel(LootMultiplier, CurrentLevel)]));
		FString Value2_Updated = "";
		StatLevel = UUpgradesUtils::GetLevelUPStatLevel(LootMultiplier, CurrentLevel);
		if (StatLevel > CurrentLevel)
			Value2_Updated = (TEXT(" -> " + FString::SanitizeFloat(LootMultiplier[StatLevel])));

		FString Value3 = TEXT("Speed Bonus : " + FString::SanitizeFloat(MaxSpeed[UUpgradesUtils::GetStatLevel(MaxSpeed, CurrentLevel)]));
		FString Value3_Updated = "";
		StatLevel = UUpgradesUtils::GetLevelUPStatLevel(MaxSpeed, CurrentLevel);
		if (StatLevel > CurrentLevel)
			Value3_Updated = (TEXT(" -> " + FString::SanitizeFloat(MaxSpeed[StatLevel])));


		if (Health[UUpgradesUtils::GetStatLevel(Health, CurrentLevel)] != 0)
		{
			output.Emplace(Value0, Value0_Updated);
		}

		if (DamageBonus[UUpgradesUtils::GetStatLevel(DamageBonus, CurrentLevel)] != 0)
		{
			output.Emplace(Value1, Value1_Updated);
		}

		if (LootMultiplier[UUpgradesUtils::GetStatLevel(LootMultiplier, CurrentLevel)] != 0)
		{
			output.Emplace(Value2, Value2_Updated);
		}

		if (MaxSpeed[UUpgradesUtils::GetStatLevel(MaxSpeed, CurrentLevel)] != 0)
		{
			output.Emplace(Value3, Value3_Updated);
		}
		

		return output;
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
