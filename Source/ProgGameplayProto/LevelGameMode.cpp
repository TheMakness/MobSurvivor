// Copyright Epic Games, Inc. All Rights Reserved.

#include "LevelGameMode.h"

#include "BonusManager.h"
#include "EnemySpawnerManager.h"
#include "GameLevelData.h"
#include "MobSurvivorInstance.h"
#include "LevelGameState.h"
#include "UpgradesManager.h"
#include "HTTP/UHttpRequestSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

void ALevelGameMode::BeginPlay()
{
	Super::BeginPlay();
	ALevelGameState* GS = GetGameState<ALevelGameState>();
	if (IsValid(GS))
	{
		GS->OnTimerFinish.AddDynamic(this, &ALevelGameMode::Win);
	}

	UMobSurvivorInstance* GI = GetGameInstance<UMobSurvivorInstance>();
	if(IsValid(GI) && IsValid(GS))
	{
		GameLevelData = GI->GameLevelData;
		GS->SetGameDuration(GameLevelData->GameDuration);
		GS->SetGoldBonus(GI->GameLevelData->GoldBonus);
	}

	StartGame();
}

ALevelGameMode::ALevelGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ALevelGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

}


void ALevelGameMode::StartGame()
{
	EnemySpawnerManager = GetWorld()->SpawnActor<AEnemySpawnerManager>();
	BonusManager = GetWorld()->SpawnActor<ABonusManager>();
	
	GetGameState<ALevelGameState>()->SetGameStarted(true);
}

void ALevelGameMode::SetGamePaused(bool Paused)
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController((GetWorld())));
	if (IsValid(MyPlayer))
	{
		
		MyPlayer->SetPause(Paused);
		bIsPaused = Paused;
	}
}

void ALevelGameMode::ReturnToMainMenu()
{
	UHttpRequestSubsystem* HTTP = GetGameInstance()->GetSubsystem<UHttpRequestSubsystem>();
	if (IsValid(HTTP))
	{
		if (HTTP->IsLoggedIn())
		{
			const float GameTime = GetGameState<ALevelGameState>()->GetGameTime();
			const int KilledEnemies = GetGameState<ALevelGameState>()->GetNumKilledEnemies();
			int GameType = 0;
			if (GetGameState<ALevelGameState>()->GetGameDuration() > 300)
			{
				GameType = 1;
			}
			
			HTTP->PostScore(FAPIScore(GameType, "", KilledEnemies, GameTime));
		}
	}
	
	UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");
}

void ALevelGameMode::GameOver()
{

	OnBeforeGameOver.Broadcast();
	SetGamePaused(true);
	bIsGameOver = true;
}

void ALevelGameMode::Win()
{
	SetGamePaused(true);
	GetGameInstance<UMobSurvivorInstance>()->AddGold(GetGameState<ALevelGameState>()->GetBonusGold());
}
