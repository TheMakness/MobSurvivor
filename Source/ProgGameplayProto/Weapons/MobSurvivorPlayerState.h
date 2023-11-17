// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MobSurvivorPlayerState.generated.h"

class APower;
class UWeaponData;
class UPowerPermanentUpgrade;
class UWeaponPermanentUpgrade;
class UEffectPermanentUpgrade;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AMobSurvivorPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddStatUpgrade(UEffectPermanentUpgrade* Upgrade);

	UFUNCTION(BlueprintCallable)
	void RemoveStatUpgrade(UEffectPermanentUpgrade* Upgrade);
	
	UFUNCTION(BlueprintCallable)
	void SetWeapon(UWeaponData* NewWeapon);
	
	UFUNCTION(BlueprintCallable)
	void SetPower(const TSubclassOf<APower> NewPower);

	UFUNCTION(BlueprintCallable)
	bool IsWeaponEquipped(UWeaponData* WeaponToCheck) const;

	UFUNCTION(BlueprintCallable)
	bool IsPowerEquipped(const TSubclassOf<APower> PowerToCheck) const;

	UFUNCTION(BlueprintCallable)
	bool IsStatUpgradeEquipped(UEffectPermanentUpgrade* Upgrade) const;

protected:
	TArray<UEffectPermanentUpgrade*> EnabledStatUpgrades;

	TObjectPtr<UWeaponData> Weapon;
	TSubclassOf<APower> Power;
};
