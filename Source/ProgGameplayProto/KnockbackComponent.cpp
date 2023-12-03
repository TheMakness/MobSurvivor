// Fill out your copyright notice in the Description page of Project Settings.


#include "KnockbackComponent.h"


// Sets default values for this component's properties
UKnockbackComponent::UKnockbackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UKnockbackComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	// ...
	
}


// Called every frame
void UKnockbackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void UKnockbackComponent::Knockback(float Force, FVector Direction)
{
	Owner->AddActorWorldOffset(Direction * Force);
}


