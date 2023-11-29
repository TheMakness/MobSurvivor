// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgGameplayProtoGameState.h"

#include "MobSurvivorInstance.h"

AProgGameplayProtoGameState::AProgGameplayProtoGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	
	
}

void AProgGameplayProtoGameState::BeginPlay()
{
	Super::BeginPlay();
	UMobSurvivorInstance* GI = GetGameInstance<UMobSurvivorInstance>();
	if (IsValid(GI))
	{
		GameTargetDuration = GI->GetGameDuration();
	}
}

void AProgGameplayProtoGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bHasGameStarted)
	{
		GameTime += DeltaSeconds;
		if (GetRemainingTime() <= 0 )
		{
			OnTimerFinish.Broadcast();
		}
	}
		

	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Game Time: " + FString::SanitizeFloat(GameTime));
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Remaining Time: " + FString::SanitizeFloat(GetRemainingTime()));
}

void AProgGameplayProtoGameState::SetGameStarted(const bool HasGameStarted)
{
	bHasGameStarted = HasGameStarted;
}
