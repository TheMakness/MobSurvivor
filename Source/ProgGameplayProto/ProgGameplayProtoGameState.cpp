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
	
		
	
}

void AProgGameplayProtoGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bHasGameStarted && bHasTimer)
	{
		GameTime += DeltaSeconds;
		if (GetRemainingTime() <= 0 )
		{
			OnTimerFinish.Broadcast();
		}
	}
		

	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Game Time: " + FString::SanitizeFloat(GameTime));
	if(bHasTimer)
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Remaining Time: " + FString::SanitizeFloat(GetRemainingTime()));
}

void AProgGameplayProtoGameState::SetGameDuration(float Duration)
{
	GameTargetDuration = Duration * 60;
	if (GameTargetDuration <= 0)
		bHasTimer = false;
}

void AProgGameplayProtoGameState::SetGameStarted(const bool HasGameStarted)
{
	bHasGameStarted = HasGameStarted;
}
