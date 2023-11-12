// Fill out your copyright notice in the Description page of Project Settings.


#include "Power.h"

// Sets default values
APower::APower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsCountdownStart = false;
	CountdownStartValue = 10;
	Countdown = CountdownStartValue;
}

// Called when the game starts or when spawned
void APower::BeginPlay()
{
	Super::BeginPlay();
	Countdown = CountdownStartValue;
}

void APower::Use_Implementation()
{
	//Cannot Use if Cooldown is not finish
	if (IsCountdownStart) 
	return;

	IsCountdownStart = true;
}

// Called every frame
void APower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Cooldown(DeltaTime);
}

void APower::Cooldown(float DeltaTime)
{
	if (IsCountdownStart && Countdown > 0)
	{
		Countdown -= DeltaTime;
	}
	else
	{
		if (IsCountdownStart)
		{
			Countdown = CountdownStartValue;
			IsCountdownStart = false;
		}
	}
}






