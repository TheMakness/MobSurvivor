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
	
}

void AUpgradesManager::BeginPlay()
{
	Super::BeginPlay();
	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GI))
	{
		
		GI->OnLevelChange.AddDynamic(this, &AUpgradesManager::LoadInGameInstance);

		if(!GI->IsAlreadyLoaded())
			LoadDefaultUpgrades();

		if(GI->CanLoad())
		{
			LoadFromGameInstance();
			GI->SwitchCanLoadState();
		}
	}
	
}



const TArray<FPermanentUpgrade>& AUpgradesManager::GetAllUpgrades() const
{
	return Upgrades;
}


void AUpgradesManager::LoadDefaultUpgrades()
{
	
	Upgrades = DefaultsUpgrades->Upgrades;
	for (FPermanentUpgrade &Upgrade : Upgrades)
	{
		
		if (Upgrade.Data->bIsDefaultPurchased)
		{
			Upgrade.bPurchased = true;
			EquipUpgrade(Upgrade.Data);
		}
	}

	
}

void AUpgradesManager::LoadInGameInstance()
{
	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(IsValid(GI))
	{
		GI->SetEquippedWeapon(GetEquippedWeapon());
		GI->SetEquippedPower(GetEquippedPower());
		GI->SetEquippedStatsUpgrades(GetEquippedStatsUpgrades());
		GI->SetUpgrades(Upgrades);

		GI->SwitchCanLoadState();
	}
}

void AUpgradesManager::LoadFromGameInstance()
{
	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GI))
	{
			EquippedWeapon = GI->GetEquippedWeapon();
			EquippedPower = GI->GetEquippedPower();
			EquippedStatsUpgrades = GI->GetEquippedStatsUpgrades();
			Upgrades = GI->GetUpgrades();


	}
}

void AUpgradesManager::SetEquippedWeapon(const TObjectPtr<UWeaponData>& Weapon)
{
	EquippedWeapon = Weapon;
}

void AUpgradesManager::SetEquippedPower(const TObjectPtr<UPowerPUData>& Power)
{
	EquippedPower = Power;
}

void AUpgradesManager::SetEquippedStatsUpgrades(const TArray<TObjectPtr<UPlayerStatsPUData>>& StatsUpgrades)
{
	EquippedStatsUpgrades = StatsUpgrades;
}



 void AUpgradesManager::LoadUpgradesFromSave(const TArray<FPermanentUpgrade>& LoadedUpgrades)
{
	
	for (FPermanentUpgrade LoadUpgrade : LoadedUpgrades)
	{
		FPermanentUpgrade* FindUpgrade = Upgrades.FindByPredicate([&LoadUpgrade](const FPermanentUpgrade& Item) -> bool
		{
				return LoadUpgrade.Data == Item.Data
			&& LoadUpgrade.bPurchased;
		});

		if (FindUpgrade != nullptr)
		{
			FindUpgrade->bPurchased = LoadUpgrade.bPurchased;
			if (FindUpgrade->Data->GetType() == EType::PlayerStats)
				EquipUpgrade(FindUpgrade->Data);
		}
	}
	
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
		EquippedStatsUpgrades.AddUnique(Cast<UPlayerStatsPUData>(UpgradeData));
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

TObjectPtr<UPowerPUData> AUpgradesManager::GetEquippedPower() const
{
	return EquippedPower;
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
