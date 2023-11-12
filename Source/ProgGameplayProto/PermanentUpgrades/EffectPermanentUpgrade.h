// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePermanentUpgrade.h"
#include "EffectPermanentUpgrade.generated.h"

class APlayerCharacter;
/**
 * Permanent Upgrade that are just effect modified applied to the player character when a new game is started
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UEffectPermanentUpgrade : public UBasePermanentUpgrade
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ApplyUpgrade(APlayerCharacter* Player);
};
