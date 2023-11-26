// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradesManager.h"

#include "MobSurvivorInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PermanentUpgrades/PermanentUpgrade.h"
#include "PermanentUpgrades/PermanentUpgradeDataList.h"
#include "PermanentUpgrades/PlayerStatsPUData.h"
#include "PermanentUpgrades/PowerPUData.h"
#include "Weapons/WeaponData.h"

AUpgradesManager::AUpgradesManager()
{
	static ConstructorHelpers::FObjectFinder<UPermanentUpgradeDataList> PermanentUpgradeList(TEXT("/Game/Data/PermanentUpgrades/DA_PermanentUpgradeList"));
	if (PermanentUpgradeList.Succeeded())
	{
		DefaultsUpgrades = PermanentUpgradeList.Object;
	}
	SetAllUpgrades();
}

void AUpgradesManager::BeginPlay()
{
	Super::BeginPlay();
	
}



const TArray<FPermanentUpgrade>& AUpgradesManager::GetAllUpgrades() const
{
	return Upgrades;
}

void AUpgradesManager::SetAllUpgrades()
{
	Upgrades = DefaultsUpgrades->Upgrades;
}

void AUpgradesManager::EquipUpgrade(UPermanentUpgradeData* UpgradeToEquip)
{
	const FPermanentUpgrade* FoundUpgrade = Upgrades.FindByPredicate([&UpgradeToEquip](const FPermanentUpgrade& Item) -> bool
	{
		return Item.Data == UpgradeToEquip;
	});
	
	// Cannot equip an upgrade not purchased
	if (!FoundUpgrade->bPurchased) return;
	
	UPermanentUpgradeData* UpgradeData = FoundUpgrade->Data;

	switch (UpgradeData->GetType())
	{
	case Power:
		EquippedPower = Cast<UPowerPUData>(UpgradeData);
		break;
	case Weapon:
		EquippedWeapon = Cast<UWeaponData>(UpgradeData);
		break;
	case PlayerStats:
		EquippedStatsUpgrades.Add(Cast<UPlayerStatsPUData>(UpgradeData));
	default:
		break;
	}
}

bool AUpgradesManager::IsWeaponEquipped(UWeaponData* UpgradeToCheck)
{
	return EquippedWeapon == UpgradeToCheck;
}

bool AUpgradesManager::IsPowerEquipped(UPowerPUData* UpgradeToCheck)
{
	return EquippedPower == UpgradeToCheck;
}

bool AUpgradesManager::IsPlayerStatsEquipped(UPlayerStatsPUData* UpgradeToCheck)
{
	return EquippedStatsUpgrades.Contains(UpgradeToCheck);
}

TArray<TObjectPtr<UPlayerStatsPUData>> AUpgradesManager::GetEquippedStatsUpgrades() const
{
	return EquippedStatsUpgrades;
}

TObjectPtr<UWeaponData> AUpgradesManager::GetEquippedWeapon() const
{
	return EquippedWeapon;
}

void AUpgradesManager::BuyUpgrade(UPermanentUpgradeData* UpgradeToBuy)
{
	FPermanentUpgrade* FoundUpgrade = Upgrades.FindByPredicate([UpgradeToBuy](const FPermanentUpgrade& Item) -> bool
	{
		return Item.Data == UpgradeToBuy;
	});

	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(IsValid(GI) && GI->GetGoldAmount() > UpgradeToBuy->Cost)
	{
		GI->AddGold(-UpgradeToBuy->Cost);
		FoundUpgrade->bPurchased = true;
	}
		
}
