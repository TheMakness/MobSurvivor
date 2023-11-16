// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePermanentUpgrade.h"
#include "PowerPermanentUpgrade.generated.h"

class APower;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROGGAMEPLAYPROTO_API UPowerPermanentUpgrade : public UBasePermanentUpgrade
{
	GENERATED_BODY()

public:
	TSubclassOf<APower> GetPower() const;
	
protected:
	// The super power referenced by this permanent upgrade
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APower> PowerReference;
};
