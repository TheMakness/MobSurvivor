// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"

#include "Player/PlayerCharacter.h"

APlayerCharacter* UGameUtils::GetMainCharacter()
{
	return APlayerCharacter::Instance;
}
