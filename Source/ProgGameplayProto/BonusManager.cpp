// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusManager.h"

#include "GameLevelData.h"
#include "LevelGameMode.h"
#include "MobSurvivorInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PermanentUpgrades/PlayerStatsPUData.h"
#include "PermanentUpgrades/PowerPUData.h"
#include "Weapons/WeaponData.h"

void ABonusManager::BeginPlay()
{
	Super::BeginPlay();

	LoadBonuses();
}

void ABonusManager::LoadBonuses()
{
	const ALevelGameMode* GameMode = Cast<ALevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	const UGameLevelData* GameLevelData = GameMode->GameLevelData;

	if (!IsValid(GameLevelData)) return;

	AllBonuses = GameLevelData->Bonuses;
	
	LoadBonusesFromUpgrades();
	
	AvailableBonuses = AllBonuses;
}

UBonusData* ABonusManager::GetRandomBonus()
{
	if (AvailableBonuses.Num() < 1)
	{
		AvailableBonuses = AllBonuses;
	}

	UBonusData* Output = AvailableBonuses[FMath::RandRange(0, AvailableBonuses.Num() - 1)];
	AvailableBonuses.Remove(Output);

	return Output;
}

void ABonusManager::LoadBonusesFromUpgrades()
{
	const UMobSurvivorInstance* GameInstance = GetGameInstance<UMobSurvivorInstance>();

	if (GameInstance->GetEquippedPower() != nullptr)
	{
		AllBonuses.Append(GameInstance->GetEquippedPower()->LinkedBonuses);
	}

	if (GameInstance->GetEquippedWeapon() != nullptr)
	{
		AllBonuses.Append(GameInstance->GetEquippedWeapon()->LinkedBonuses);
	}

	if (!GameInstance->GetEquippedStatsUpgrades().IsEmpty())
	{
		for (const auto StatsUpgrades : GameInstance->GetEquippedStatsUpgrades())
		{
			AllBonuses.Append(StatsUpgrades->LinkedBonuses);
		}
	}
}
