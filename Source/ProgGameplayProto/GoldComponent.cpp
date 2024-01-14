// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldComponent.h"

#include "MobSurvivorInstance.h"
#include "LevelGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGoldComponent::UGoldComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGoldComponent::AddGold(const int GoldValue)
{
	GoldAmount += GoldValue * BonusGoldMultiplier;
	OnGoldChanged.Broadcast(GoldAmount);
}


// Called when the game starts
void UGoldComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<ALevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->OnBeforeGameOver.AddDynamic(this, &UGoldComponent::SaveGold);
	// ...
}

void UGoldComponent::SaveGold()
{
	UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
	if (IsValid(GI))
	{
		Cast<UMobSurvivorInstance>(GI)->AddGold(GoldAmount);
	}
}


// Called every frame
void UGoldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UGoldComponent::IncrementGoldMultiplier(const float IncrementValue)
{
	BonusGoldMultiplier += IncrementValue;
}
