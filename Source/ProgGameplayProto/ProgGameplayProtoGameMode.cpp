// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProgGameplayProtoGameMode.h"

#include "BonusManager.h"
#include "EnemySpawnerManager.h"
#include "GameLevelData.h"
#include "MobSurvivorInstance.h"
#include "ProgGameplayProtoGameState.h"
#include "UpgradesManager.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

void AProgGameplayProtoGameMode::BeginPlay()
{
	Super::BeginPlay();
	AProgGameplayProtoGameState* GS = GetGameState<AProgGameplayProtoGameState>();
	if (IsValid(GS))
	{
		GS->OnTimerFinish.AddDynamic(this, &AProgGameplayProtoGameMode::Win);
	}

	UMobSurvivorInstance* GI = GetGameInstance<UMobSurvivorInstance>();
	if(IsValid(GI) && IsValid(GS))
	{
		GameLevelData = GI->DA_Level;
		GS->SetGameDuration(GameLevelData->GameDuration);
		GS->SetGoldBonus(GI->DA_Level->GoldBonus);
	}
}

AProgGameplayProtoGameMode::AProgGameplayProtoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}


	

}

void AProgGameplayProtoGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}


void AProgGameplayProtoGameMode::StartGame()
{
	EnemySpawnerManager = GetWorld()->SpawnActor<AEnemySpawnerManager>();
	BonusManager = GetWorld()->SpawnActor<ABonusManager>();
	
	GetGameState<AProgGameplayProtoGameState>()->SetGameStarted(true);
}

void AProgGameplayProtoGameMode::SetGamePaused(bool Paused)
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController((GetWorld())));
	if (IsValid(MyPlayer))
	{
		
		MyPlayer->SetPause(Paused);
		bIsPaused = Paused;
	}
}

void AProgGameplayProtoGameMode::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");
}

void AProgGameplayProtoGameMode::GameOver()
{

	OnBeforeGameOver.Broadcast();
	SetGamePaused(true);
	bIsGameOver = true;
}

void AProgGameplayProtoGameMode::Win()
{
	SetGamePaused(true);
	GetGameInstance<UMobSurvivorInstance>()->AddGold(GetGameState<AProgGameplayProtoGameState>()->GetBonusGold());
}
