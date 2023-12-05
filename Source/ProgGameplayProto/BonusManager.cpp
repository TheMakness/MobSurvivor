// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusManager.h"

#include "GameLevelData.h"
#include "LevelGameMode.h"
#include "Kismet/GameplayStatics.h"

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