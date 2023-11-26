// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgGameplayMenuGameMode.h"

#include "MainMenuPlayerState.h"

AProgGameplayMenuGameMode::AProgGameplayMenuGameMode()
{
	// set default game state class
	PlayerStateClass = AMainMenuPlayerState::StaticClass();

}

