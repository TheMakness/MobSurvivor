// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePermanentUpgrade.h"
#include "ProgGameplayProto/Weapons/WeaponData.h"
#include "WeaponPermanentUpgrade.generated.h"

/**
 * Type of Permanent Upgrade that hold a Weapon
 */
UCLASS(Abstract, Blueprintable)
class PROGGAMEPLAYPROTO_API UWeaponPermanentUpgrade : public UBasePermanentUpgrade
{
	GENERATED_BODY()
	
public:
	UWeaponData* GetWeapon() const;
	
protected:
	// The weapon that this permanent upgrade reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponData* WeaponReference;
};
