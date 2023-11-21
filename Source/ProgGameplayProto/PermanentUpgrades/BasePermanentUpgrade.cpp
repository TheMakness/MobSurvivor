// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePermanentUpgrade.h"

bool UBasePermanentUpgrade::IsPurchasable() const
{
	return bIsPurchasable;
}

bool UBasePermanentUpgrade::IsPurchased() const
{
	return bIsPurchased;
}
int UBasePermanentUpgrade::GetBaseCost() const
{
	return Cost;
}

int UBasePermanentUpgrade::CalculateCost() const
{
	return Level * (Cost * CostMultiplierPerLevel);
}
