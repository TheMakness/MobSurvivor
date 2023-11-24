// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MobSurvivorSaveGame.generated.h"

class UMobSurvivorInstance;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int GoldAmount;
	FString SaveSlotName;

protected:
	int Index;

public:
	UMobSurvivorSaveGame();
};
