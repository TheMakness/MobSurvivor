// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePermanentUpgrade.h"
#include "EffectPermanentUpgrade.generated.h"

class APlayerCharacter;
/**
 * Permanent Upgrade that affect player stats and effects like health, shield, etc.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class PROGGAMEPLAYPROTO_API UEffectPermanentUpgrade : public UBasePermanentUpgrade
{
	GENERATED_BODY()
	
public:
	/**
	 * Apply an upgrade on player
	 * @param Player The player to apply the upgrade on
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void ApplyUpgrade(APlayerCharacter* Player);

	friend bool operator==(const UEffectPermanentUpgrade& Lhs, const UEffectPermanentUpgrade& RHS)
	{
		return static_cast<const UBasePermanentUpgrade&>(Lhs) == static_cast<const UBasePermanentUpgrade&>(RHS);
	}

	friend bool operator!=(const UEffectPermanentUpgrade& Lhs, const UEffectPermanentUpgrade& RHS)
	{
		return !(Lhs == RHS);
	}
};
