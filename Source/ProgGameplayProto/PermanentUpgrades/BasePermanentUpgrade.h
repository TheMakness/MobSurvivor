// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BasePermanentUpgrade.generated.h"

class UPermanentUpgradeData;

/**
 * 
 */
UCLASS(Blueprintable)
class PROGGAMEPLAYPROTO_API UBasePermanentUpgrade : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintType)
	UPermanentUpgradeData* Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPurchasable = false;
};
