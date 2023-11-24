// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PermanentUpgradeData.generated.h"

UENUM(BlueprintType)
enum EType
{
	Base UMETA(Hidden),
	Weapon,
	Power,
	PlayerStats,
};

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class PROGGAMEPLAYPROTO_API UPermanentUpgradeData : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual FORCEINLINE EType GetType() const
	{
		return EType::Base;
	}
	
	// Display name of the permanent upgrade, displayed in the shop menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", meta = (MultiLine = true))
	FString Description;

	// Logo to display in the Shop UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata")
	UTexture2D* Image;

	// Cost in coins of the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata")
	int Cost;

	// If this upgrade is purchased by default when starting a new game (which means that it is a default upgrade)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata")
	bool bIsDefaultPurchased = false;
	
private:
	friend bool operator==(const UPermanentUpgradeData& Lhs, const UPermanentUpgradeData& RHS)
	{
		return Lhs.Name == RHS.Name
			&& Lhs.Description == RHS.Description
			&& Lhs.Image == RHS.Image
			&& Lhs.Cost == RHS.Cost;
	}

	friend bool operator!=(const UPermanentUpgradeData& Lhs, const UPermanentUpgradeData& RHS)
	{
		return !(Lhs == RHS);
	}
};
