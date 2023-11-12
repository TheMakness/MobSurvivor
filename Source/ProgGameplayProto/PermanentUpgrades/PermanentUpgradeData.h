// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PermanentUpgradeData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UPermanentUpgradeData : public UDataAsset
{
	GENERATED_BODY()

public:
	// Display name of the permanent upgrade, displayed in the shop menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	// Cost in coins of the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Cost;

	// TODO add multiplier of the cost per level
	
	// Maximum level for the upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLevel = 1;
};
