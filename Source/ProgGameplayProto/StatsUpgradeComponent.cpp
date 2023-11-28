// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsUpgradeComponent.h"

#include "GameUtils.h"
#include "Health.h"
#include "MobSurvivorInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PermanentUpgrades/PlayerStatsPUData.h"
#include "Player/PlayerCharacter.h"

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

	for (TObjectPtr<UPlayerStatsPUData> PlayerStatsPuData : StatsUpgrades)
	{
		Health->AddHealth(PlayerStatsPuData->Health);
		CharacterMovement->MaxWalkSpeed += PlayerStatsPuData->MaxSpeed;
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

