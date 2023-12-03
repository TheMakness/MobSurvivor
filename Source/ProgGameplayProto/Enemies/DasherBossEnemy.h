// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "DasherBossEnemy.generated.h"

/**
 * Boss enemy that tries to dash into the Player
 */
UCLASS(Abstract)
class PROGGAMEPLAYPROTO_API ADasherBossEnemy : public AEnemy
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (Units = Centimeters))
	float DistanceBeforeDash;

	// The exponential value for the EaseInOut interpolation function
	UPROPERTY(EditAnywhere)
	float DashExponentialInterpValue;
	
	FVector DashStartLocation;

	FVector DashEndLocation;

	UPROPERTY(EditAnywhere)
	float DashEndLocationOffset;
	
	// Time of the dash (the smaller the value, the quicker the dash will be going from Start to End)
	UPROPERTY(EditAnywhere, meta = (Units = Seconds))
	float DashDuration;

	// Keep track of running timer value
	float DashTimer;

	bool bDashTimerStarted;

	// Time before enemy can attack again 
	UPROPERTY(EditAnywhere, meta = (Units = Seconds))
	float DashCooldown;

	// Keep track of current cooldown value
	float DashCooldownTime;

	bool bIsCooldownActive;
	
	UPROPERTY(EditAnywhere, meta = (Units = Seconds))
	float AttackRate;

	FTimerHandle AttackTimerHandle;

	FTimerDelegate AttackTimerDelegate;

public:
	ADasherBossEnemy();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

protected:
	virtual void MoveTowardPlayer(float DeltaTime) override;

private:
	void DashTowardPlayer(const float DeltaTime);

	void ResetAttackCooldown();

	/**
	 * Update cooldown time value and check if cooldown ended
	 * 
	 * @param DeltaTime 
	 */
	void UpdateAttackCooldown(const float DeltaTime);

	void ResetDashTimer();

	void StopDashTimer();

};
