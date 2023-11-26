// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PermanentUpgradeDataList.generated.h"

struct FPermanentUpgrade;
/**
 * 
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UPermanentUpgradeDataList : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPermanentUpgrade> Upgrades;
};
