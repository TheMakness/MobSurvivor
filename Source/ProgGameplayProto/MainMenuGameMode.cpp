// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "MainMenuPlayerState.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	// set default game state class
	PlayerStateClass = AMainMenuPlayerState::StaticClass();

}

