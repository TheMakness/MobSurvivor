// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"

#include "MobSurvivorInstance.h"
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

	if (IsValid(SaveGameInstance))
	{
		SaveGameInstance->GoldAmount = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(WorldContext))->GetGoldAmount();
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 0);
	}
}

bool UGameUtils::LoadGame(UObject* WorldContext)
{
	UMobSurvivorInstance* GameInstance = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(WorldContext));
	if (!IsValid(GameInstance))
		return false;

	if(GameInstance->GetAlreadyLoad())
		return false;

	UMobSurvivorSaveGame* LoadedGame = Cast<UMobSurvivorSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("InstanceSave"), 0));
	GameInstance->SwitchAreadyLoadState();
	if (IsValid(LoadedGame))
	{
		GameInstance->AddGold(LoadedGame->GoldAmount);
		return true;
	}
		return false;
	
}


