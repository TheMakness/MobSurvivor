// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"

#include "MainMenuPlayerState.h"
#include "MobSurvivorInstance.h"
#include "ProgGameplayMenuGameMode.h"
#include "UpgradesManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "Save/MobSurvivorSaveGame.h"

APlayerCharacter* UGameUtils::GetMainCharacter()
{
	return APlayerCharacter::Instance;
}

void UGameUtils::SaveGame(UObject* WorldContext)
{
	UMobSurvivorSaveGame* SaveGameInstance = Cast<UMobSurvivorSaveGame>(UGameplayStatics::CreateSaveGameObject(UMobSurvivorSaveGame::StaticClass()));
	AMainMenuPlayerState* PlayerState = Cast<AMainMenuPlayerState>(UGameplayStatics::GetPlayerState(WorldContext,0));

	if (IsValid(SaveGameInstance) && IsValid(PlayerState))
	{
		SaveGameInstance->GoldAmount = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(WorldContext))->GetGoldAmount();
		SaveGameInstance->PermanentUpgrades = PlayerState->GetUpgradesManager()->GetAllUpgrades();
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 0);
	}
}

bool UGameUtils::LoadGame(UObject* WorldContext)
{
	UMobSurvivorInstance* GameInstance = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(WorldContext));
	if (!IsValid(GameInstance))
		return false;

	AMainMenuPlayerState* PlayerState = Cast<AMainMenuPlayerState>(UGameplayStatics::GetPlayerState(WorldContext, 0));
	if (!IsValid(PlayerState))
		return false;

	if(GameInstance->GetAlreadyLoad())
		return false;

	UMobSurvivorSaveGame* LoadedGame = Cast<UMobSurvivorSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("InstanceSave"), 0));
	GameInstance->SwitchAreadyLoadState();
	if (IsValid(LoadedGame))
	{
		GameInstance->AddGold(LoadedGame->GoldAmount);
		PlayerState->GetUpgradesManager()->LoadUpgradesFromSave(LoadedGame->PermanentUpgrades);
		return true;
	}
		return false;
	
}

void UGameUtils::DeleteSave()
{
	UGameplayStatics::DeleteGameInSlot(TEXT("InstanceSave"), 0);
}

void UGameUtils::ChangeLevel(UObject* WorldContext, FName LevelName)
{
	FOnLevelChange Event = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(WorldContext))->OnLevelChange;
	Event.Broadcast();
	UGameplayStatics::OpenLevel(WorldContext, LevelName);
}


