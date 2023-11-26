// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorInstance.h"


void UMobSurvivorInstance::AddGold(int NewGold)
{
	GoldAmount += NewGold;
	OnGoldChange.Broadcast();
}

void UMobSurvivorInstance::SwitchAreadyLoadState()
{
	bHasAlreadyLoadSave = true;
}
