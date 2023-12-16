// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerComponent.h"

#include "Misc/DataValidation.h"
#include <ProgGameplayProto/PermanentUpgrades/UUpgradesUtils.h>

#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/MobSurvivorInstance.h"
#include "ProgGameplayProto/PermanentUpgrades/PermanentUpgrade.h"
#include "ProgGameplayProto/PermanentUpgrades/PowerPUData.h"

// Sets default values for this component's properties
UPowerComponent::UPowerComponent() : Countdown(CountdownStartValue), bHasCountdownStarted(false), CountdownStartValue(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPowerComponent::Initialise(APlayerCharacter* Player)
{
	PlayerOwner = Player;
}

const APlayerCharacter* UPowerComponent::GetPlayerOwner() const
{
	return PlayerOwner;
}


// Called when the game starts
void UPowerComponent::BeginPlay()
{
	Super::BeginPlay();

	// PowerData can't be null because it is being checked in IsDataValid.
	// The Assertion is here in case there is an issue during the Data Validation check
	checkf(IsValid(PowerData), TEXT("Power Data must be set in the Details panel."));
	
	CountdownStartValue = PowerData->CooldownTime[UUpgradesUtils::GetStatLevel(PowerData->CooldownTime, CurrentPowerLevel)];
	Countdown = CountdownStartValue;
	if (ensureAlwaysMsgf(PowerData != nullptr, TEXT("The DataAsset linked to this PowerComponent has not been set.")))
	{
		UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (IsValid(GI))
		{
			TArray<FPermanentUpgrade> Upgrades = GI->GetUpgrades();
			UPermanentUpgradeData* UpgradeData = Cast<UPermanentUpgradeData>(PowerData);

			FPermanentUpgrade* FoundUpgrade = Upgrades.FindByPredicate([UpgradeData](const FPermanentUpgrade& Item) -> bool
				{
					return Item.Data == UpgradeData;
				});

			CurrentPowerLevel = FoundUpgrade->CurrentLevel;

		}

		
	}
}


// Called every frame
void UPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Cooldown(DeltaTime);
}

void UPowerComponent::Use()
{
	// Can't Use() if Cooldown is not finished
	if (bHasCountdownStarted) return;

	bHasCountdownStarted = true;

	UseBehaviour();
}
EDataValidationResult UPowerComponent::IsDataValid(FDataValidationContext& Context) const
{
	
	if (!IsValid(PowerData))
	{
		Context.AddError(FText::FromString("Power Data must be set in the Details panel."));
	}
	
	return Super::IsDataValid(Context);
}

void UPowerComponent::UseBehaviour_Implementation()
{
	// Must be implemented in children BP class
}

void UPowerComponent::Cooldown(const float DeltaTime)
{
	
	if (bHasCountdownStarted && Countdown > 0)
	{
		Countdown -= DeltaTime;
	}
	else
	{
		if (bHasCountdownStarted)
		{
			Countdown = CountdownStartValue;
			bHasCountdownStarted = false;
		}
	}
}

