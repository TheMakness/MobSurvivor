// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDropperComponent.h"

#include "ProgGameplayProto/Health.h"


void UEnemyDropperComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupDropOnDie();
}

void UEnemyDropperComponent::SetupDropOnDie()
{
	UHealth* health = GetOwner()->FindComponentByClass<UHealth>();

	if (!IsValid(health)) return;

	health->OnBeforeHealthDie.AddDynamic(this, &UEnemyDropperComponent::OnEnemyDie);
}

void UEnemyDropperComponent::OnEnemyDie()
{
	Drop();
}