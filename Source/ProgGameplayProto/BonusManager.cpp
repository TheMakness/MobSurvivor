// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusManager.h"

#include "GameLevelData.h"
#include "LevelGameMode.h"
#include "Bonuses/BonusData.h"
#include "Engine/AssetManager.h"
#include "Engine/ObjectLibrary.h"
#include "Kismet/GameplayStatics.h"

void ABonusManager::BeginPlay()
{
	Super::BeginPlay();

	LoadBonuses();
}

void ABonusManager::LoadBonuses()
{
	ALevelGameMode* gameMode = Cast<ALevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	UGameLevelData* gameLevelData = gameMode->GameLevelData;

	if (!IsValid(gameLevelData)) return;

	AllBonuses = gameLevelData->Bonuses;
	AvailableBonuses = AllBonuses;
}

UBonusData* ABonusManager::GetRandomBonus()
{
	if (AvailableBonuses.Num() < 1)
	{
		AvailableBonuses = AllBonuses;
	}

	UBonusData* output = AvailableBonuses[FMath::RandRange(0, AvailableBonuses.Num() - 1)];
	AvailableBonuses.Remove(output);

	return output;
}