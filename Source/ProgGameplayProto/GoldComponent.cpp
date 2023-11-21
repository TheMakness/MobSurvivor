// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldComponent.h"

// Sets default values for this component's properties
UGoldComponent::UGoldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	GoldAmount = 0;
	// ...
}


void UGoldComponent::AddGold(int GoldValue)
{
	GoldAmount += GoldValue;
	OnGoldChanged.Broadcast(GoldAmount);
}


// Called when the game starts
void UGoldComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGoldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

