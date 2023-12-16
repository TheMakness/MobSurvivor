// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerState.h"

#include "GameUtils.h"
#include "UpgradesManager.h"
#include "PermanentUpgrades/PlayerStatsPUData.h"

AUpgradesManager* AMainMenuPlayerState::GetUpgradesManager() const
{
	return UpgradesManager;
}

void AMainMenuPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	GetPlayerController()->SetShowMouseCursor(true);
	
	auto InputMode = FInputModeGameAndUI();
	InputMode.SetHideCursorDuringCapture(false);

	GetPlayerController()->SetInputMode(InputMode);
	
	UpgradesManager = GetWorld()->SpawnActor<AUpgradesManager>();
	UGameUtils::LoadGame(GetWorld());
}
