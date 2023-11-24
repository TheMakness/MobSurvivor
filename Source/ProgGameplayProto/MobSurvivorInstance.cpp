// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorInstance.h"


void UMobSurvivorInstance::AddGold(int NewGold)
{
	GoldAmount += NewGold;
}

void UMobSurvivorInstance::SwitchAreadyLoadState()
{
	bHasAlreadyLoadSave = true;
}
