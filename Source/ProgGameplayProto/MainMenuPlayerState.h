// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainMenuPlayerState.generated.h"

class AUpgradesManager;
class UPowerPUData;
class UPlayerStatsPUData;
class UPermanentUpgradeData;
class UWeaponData;

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AMainMenuPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	AUpgradesManager* GetUpgradesManager() const;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AUpgradesManager* UpgradesManager;
};
