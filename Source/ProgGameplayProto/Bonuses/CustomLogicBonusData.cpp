// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLogicBonusData.h"

#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"

void UCustomLogicBonusData::ApplyOnMainCharacter()
{
	const APlayerCharacter* MainCharacter = UGameUtils::GetMainCharacter();
	if (!IsValid(MainCharacter)) return;
	
	MainCharacter->GetWorld()->SpawnActor(CustomLogicActor, &MainCharacter->GetActorTransform());
}
