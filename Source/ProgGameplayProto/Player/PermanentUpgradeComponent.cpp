// Fill out your copyright notice in the Description page of Project Settings.


#include "PermanentUpgradeComponent.h"

#include "ProgGameplayProto/PermanentUpgrades/EffectPermanentUpgrade.h"
#include "PlayerCharacter.h"
#include "ProgGameplayProto/GameUtils.h"


// Sets default values for this component's properties
UPermanentUpgradeComponent::UPermanentUpgradeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPermanentUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UEffectPermanentUpgrade> EffectUpgrade : ActiveEffectUpgrades)
	{
		if (!IsValid(EffectUpgrade)) continue;
		
		UEffectPermanentUpgrade* Instance = NewObject<UEffectPermanentUpgrade>(this, EffectUpgrade);
		InstantiatedEffectUpgrades.Add(Instance);
	}
	
	const auto Player = GetOwner<APlayerCharacter>();
	for (const auto EffectUpgrade : InstantiatedEffectUpgrades)
	{
		EffectUpgrade->ApplyUpgrade(Player);
	}
	
}

// Called every frame
void UPermanentUpgradeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

