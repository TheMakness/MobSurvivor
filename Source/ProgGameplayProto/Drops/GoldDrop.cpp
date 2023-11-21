// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldDrop.h"

#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/GoldComponent.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"

void AGoldDrop::Collect()
{
	Super::Collect();
	APlayerCharacter* mainCharacter = UGameUtils::GetMainCharacter();

	if (IsValid(mainCharacter))
	{
		mainCharacter->GetGold()->AddGold(GoldAmount);
	}
	Destroy();
}
