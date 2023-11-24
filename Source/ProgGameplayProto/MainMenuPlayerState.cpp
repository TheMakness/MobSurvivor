// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerState.h"

#include "UpgradesManager.h"
#include "PermanentUpgrades/PlayerStatsPUData.h"

AUpgradesManager* AMainMenuPlayerState::GetUpgradesManager() const
{
	return UpgradesManager;
}

void AMainMenuPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	UpgradesManager = GetWorld()->SpawnActor<AUpgradesManager>();
}
