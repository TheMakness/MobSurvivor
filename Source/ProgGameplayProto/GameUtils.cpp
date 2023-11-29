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
	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(WorldContext));

	if (IsValid(SaveGameInstance) && IsValid(PlayerState) && IsValid(GI))
	{
		PlayerState->GetUpgradesManager()->LoadInGameInstance();

		SaveGameInstance->GoldAmount = GI->GetGoldAmount();
		SaveGameInstance->PermanentUpgrades = PlayerState->GetUpgradesManager()->GetAllUpgrades();
		SaveGameInstance->EquippedWeapon = GI->GetEquippedWeapon();
		SaveGameInstance->EquippedPower = GI->GetEquippedPower();
		SaveGameInstance->EquippedStatsUpgrades = GI->GetEquippedStatsUpgrades();

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



	UMobSurvivorSaveGame* LoadedGame = Cast<UMobSurvivorSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("InstanceSave"), 0));
	
	if (IsValid(LoadedGame))
	{
		if (!GameInstance->IsAlreadyLoaded())
		{
			GameInstance->AddGold(LoadedGame->GoldAmount);

			AUpgradesManager* UpgradesManager = PlayerState->GetUpgradesManager();

			if(UpgradesManager)
			{
				UpgradesManager->SetEquippedWeapon(LoadedGame->EquippedWeapon);
				UpgradesManager->SetEquippedPower(LoadedGame->EquippedPower);
				UpgradesManager->SetEquippedStatsUpgrades(LoadedGame->EquippedStatsUpgrades);
								
				UpgradesManager->LoadUpgradesFromSave(LoadedGame->PermanentUpgrades);

				GameInstance->SwitchAlreadyLoadState();
			}
			
		}

		

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
	SaveGame(WorldContext);
	UGameplayStatics::OpenLevel(WorldContext, LevelName);
}


