// Fill out your copyright notice in the Description page of Project Settings.


#include "DasherBossEnemy.h"

#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"


// Sets default values
ADasherBossEnemy::ADasherBossEnemy():
	DistanceBeforeDash(0),
	DashExponentialInterpValue(1.2),
	DashEndLocationOffset(50),
	DashCooldown(0),
	DashDuration(0),
	bDashTimerStarted(false),
	DashTimer(0),
	DashCooldownTime(0),
	bIsCooldownActive(false),
	AttackRate(5)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADasherBossEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ADasherBossEnemy::UpdateAttackCooldown(const float DeltaTime)
{
	if (bIsCooldownActive)
	{
		DashCooldownTime += DeltaTime;
		if (DashCooldownTime >= DashCooldown)
		{
			bIsCooldownActive = false;
		}
	}
}

void ADasherBossEnemy::Tick(float DeltaTime)
{
	UpdateAttackCooldown(DeltaTime);
	
	if (bDashTimerStarted)
	{
		DashTowardPlayer(DeltaTime);
	}
	else
	{
		MoveTowardPlayer(DeltaTime);
	}
}

void ADasherBossEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AttackTimerDelegate.BindUObject(this, &ADasherBossEnemy::TryAttacking, OtherActor);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, AttackRate, true);
}

void ADasherBossEnemy::NotifyActorEndOverlap(AActor* OtherActor)
{
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
}


void ADasherBossEnemy::ResetAttackCooldown()
{
	DashCooldownTime = 0;
	bIsCooldownActive = true;
}

void ADasherBossEnemy::ResetDashTimer()
{
	DashTimer = 0;
	bDashTimerStarted = true;
}

void ADasherBossEnemy::MoveTowardPlayer(float DeltaTime)
{
	const APlayerCharacter* Player = UGameUtils::GetMainCharacter();

	if (!IsValid(Player)) return;

	const FVector DeltaLocation = Player->GetActorLocation() - GetActorLocation();
	const float Distance = DeltaLocation.Length();
	
	if (!bIsCooldownActive && Distance < DistanceBeforeDash)
	{
		FVector Direction = DeltaLocation;
		Direction.Z = 0;
		Direction.Normalize();
		
		DashStartLocation = GetActorLocation();
		DashEndLocation = Player->GetActorLocation() + (Direction * DashEndLocationOffset);

		// TODO: REMOVE IF WON'T BUILD
		DrawDebugSphere(GetWorld(), Player->GetActorLocation(), 10, 64, FColor::Green, false, DashCooldown - 1);
		DrawDebugSphere(GetWorld(), DashEndLocation, 10, 64, FColor::Red, false, DashCooldown - 1);

		ResetAttackCooldown();

		ResetDashTimer();
	}
	else
	{
		FVector Direction = DeltaLocation;
		Direction.Z = 0;
		Direction.Normalize();

		const FVector Movement = Direction * MoveSpeed * DeltaTime;

		AddActorWorldOffset(Movement);
	}
}

void ADasherBossEnemy::StopDashTimer()
{
	DashTimer = 0;
	bDashTimerStarted = false;
}

void ADasherBossEnemy::DashTowardPlayer(const float DeltaTime)
{
	DashTimer += DeltaTime;
	
	const float Alpha = DashTimer / DashDuration;

	const FVector Movement = FMath::InterpEaseInOut(DashStartLocation, DashEndLocation, Alpha, DashExponentialInterpValue);
	SetActorLocation(Movement);

	// Stop Timer when interpolation is done
	if (Alpha >= 1.0f)
	{
		StopDashTimer();
	}
}
