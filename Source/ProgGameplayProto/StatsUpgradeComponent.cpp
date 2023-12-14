// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsUpgradeComponent.h"

#include "GameUtils.h"
#include "Health.h"
#include "MobSurvivorInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PermanentUpgrades/PlayerStatsPUData.h"
#include "PermanentUpgrades/Components/PermanentUpgradeComponent_Base.h"
#include "Player/PlayerCharacter.h"
#include <ProgGameplayProto/PermanentUpgrades/UUpgradesUtils.h>


// Sets default values for this component's properties
UStatsUpgradeComponent::UStatsUpgradeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStatsUpgradeComponent::ApplyUpgrades()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());
	UHealth* Health = Player->GetHealth();
	UCharacterMovementComponent* CharacterMovement = Player->GetCharacterMovement();
	TArray<TObjectPtr<UPlayerStatsPUData>> StatsUpgrades = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetEquippedStatsUpgrades();

	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	


	for (TObjectPtr<UPlayerStatsPUData> PlayerStatsPuData : StatsUpgrades)
	{
		if (IsValid(GI))
		{
			TArray<FPermanentUpgrade> Upgrades = GI->GetUpgrades();
			UPermanentUpgradeData* UpgradeData = Cast<UPermanentUpgradeData>(PlayerStatsPuData);

			FPermanentUpgrade* FoundUpgrade = Upgrades.FindByPredicate([UpgradeData](const FPermanentUpgrade& Item) -> bool
				{
					return Item.Data == UpgradeData;
				});

			CurrentUpgradeLevel = FoundUpgrade->CurrentLevel;

		}

		Health->SetMaxHealth(Health->GetMaxHealth() + PlayerStatsPuData->Health[UUpgradesUtils::GetStatLevel(PlayerStatsPuData->Health,CurrentUpgradeLevel)]);
		CharacterMovement->MaxWalkSpeed += PlayerStatsPuData->MaxSpeed[UUpgradesUtils::GetStatLevel(PlayerStatsPuData->MaxSpeed,CurrentUpgradeLevel)];
		if(PlayerStatsPuData->ActorComponent.Num() > 0)
		{
			for ( TSubclassOf<UActorComponent> Component : PlayerStatsPuData->ActorComponent)
			{
				Player->AddComponentByClass(Component,false,Player->GetTransform(),false);
			}
		}
	}
	
}


// Called when the game starts
void UStatsUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UStatsUpgradeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



