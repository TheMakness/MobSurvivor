// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerPermanentUpgrade.h"

TSubclassOf<APower> UPowerPermanentUpgrade::GetPower() const
{
	return PowerReference;
}
