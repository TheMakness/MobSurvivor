// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatsResult.h"
#include "Engine/DataAsset.h"
#include "PermanentUpgradeData.generated.h"

class UBonusData;
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

	UFUNCTION(BlueprintCallable)
		virtual TArray<FString> GetStatsStrings(int CurrentLevel) { return TArray<FString>(); };
	UFUNCTION(BlueprintCallable)
		virtual TArray<FStatsResult> GetUpdatedStatsStrings(int CurrentLevel) { return TArray<FStatsResult>(); }; ;
	
	// Display name of the permanent upgrade, displayed in the shop menu
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata", meta = (MultiLine = true))
	FString Description;

	// Logo to display in the Shop UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	UTexture2D* Image;

	// Cost in coins of the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	TMap<int,int> Cost = {{1,0}};

	// If this upgrade is purchased by default when starting a new game (which means that it is a default upgrade)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	bool bIsDefaultPurchased = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	TArray<TObjectPtr<UBonusData>> LinkedBonuses;
	bool bIsHide = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	int MaxLevel = 1;
	
private:
	friend bool operator==(const UPermanentUpgradeData& Lhs, const UPermanentUpgradeData& RHS)
	{
		return Lhs.Name == RHS.Name
			&& Lhs.Description == RHS.Description
			&& Lhs.Image == RHS.Image
			&& Lhs.LinkedBonuses == RHS.LinkedBonuses;
			&& Lhs.Cost[1] == RHS.Cost[1];
	}

	friend bool operator!=(const UPermanentUpgradeData& Lhs, const UPermanentUpgradeData& RHS)
	{
		return !(Lhs == RHS);
	}
};
