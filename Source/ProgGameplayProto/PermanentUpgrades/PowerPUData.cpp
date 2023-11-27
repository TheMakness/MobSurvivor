// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerPUData.h"

const TSubclassOf<UPowerComponent>& UPowerPUData::GetComponent() const
{
	return PowerComponent;
}
