// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BasePermanentUpgrade.generated.h"

class UPermanentUpgradeData;

enum class UpgradeType
{
	Base,
	Effect,
	Power,
	Weapon,
};

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROGGAMEPLAYPROTO_API UBasePermanentUpgrade : public UObject
{
	GENERATED_BODY()

public:
	bool IsPurchasable() const;
	bool IsPurchased() const;

protected:
	UpgradeType Type = UpgradeType::Base;
	
	// Display name of the permanent upgrade, displayed in the shop menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Logo;

	// Cost in coins of the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Cost;

	// TODO add multiplier of the cost per level
	
	// Maximum level for the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLevel = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPurchasable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPurchased = false;

	friend bool operator==(const UBasePermanentUpgrade& Lhs, const UBasePermanentUpgrade& RHS)
	{
		return Lhs.Type == RHS.Type
			&& Lhs.Name == RHS.Name
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
