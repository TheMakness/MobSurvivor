// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerComponent.h"

#include "K2Node_SpawnActorFromClass.h"
#include "Power.h"

// Sets default values for this component's properties
UPowerComponent::UPowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentPower = nullptr;
	// ...
}


// Called when the game starts
void UPowerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

