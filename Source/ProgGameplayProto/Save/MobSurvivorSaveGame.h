// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProgGameplayProto/PermanentUpgrades/PermanentUpgrade.h"
#include "MobSurvivorSaveGame.generated.h"


class UPlayerStatsPUData;
class UWeaponData;
class UPowerPUData;
class UMobSurvivorInstance;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int GoldAmount;
	FString SaveSlotName;

	UPROPERTY()
	TArray<FPermanentUpgrade> PermanentUpgrades;

	UPROPERTY()
	TArray<TObjectPtr<UPlayerStatsPUData>> EquippedStatsUpgrades;

	UPROPERTY()
	TObjectPtr<UWeaponData> EquippedWeapon;

	UPROPERTY()
	TObjectPtr<UPowerPUData> EquippedPower;

protected:
	int Index;

public:
	UMobSurvivorSaveGame();
};
