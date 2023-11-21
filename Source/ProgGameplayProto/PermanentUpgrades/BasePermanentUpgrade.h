// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BasePermanentUpgrade.generated.h"

class UPermanentUpgradeData;

/**
 * Base class of permanent upgrades, hold data relevant to every upgrades
 */
UCLASS(Abstract, Blueprintable)
class PROGGAMEPLAYPROTO_API UBasePermanentUpgrade : public UObject
{
	GENERATED_BODY()

public:
	bool IsPurchasable() const;
	bool IsPurchased() const;

	int GetBaseCost() const;

	/**
	 * Calculate the cost according to current level of the upgrade and its cost multiplier
	 * @return Calculated cost
	 */
	virtual int CalculateCost() const;

protected:
	
	// Display name of the permanent upgrade, displayed in the shop menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	// Logo to display in the Shop UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Logo;

	// Cost in coins of the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Cost;

	// Multiply the base cost of the upgrade according to its level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CostMultiplierPerLevel = 1;

	// Current level of the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level = 1; 
	
	// Maximum level for the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLevel = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPurchasable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPurchased = false;

	friend bool operator==(const UBasePermanentUpgrade& Lhs, const UBasePermanentUpgrade& RHS)
	{
		return Lhs.Name == RHS.Name
			&& Lhs.Logo == RHS.Logo
			&& Lhs.Cost == RHS.Cost
			&& Lhs.MaxLevel == RHS.MaxLevel
			&& Lhs.bIsPurchasable == RHS.bIsPurchasable
			&& Lhs.bIsPurchased == RHS.bIsPurchased;
	}

	friend bool operator!=(const UBasePermanentUpgrade& Lhs, const UBasePermanentUpgrade& RHS)
	{
		return !(Lhs == RHS);
	}
};
