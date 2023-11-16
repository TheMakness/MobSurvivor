// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.h"
#include "WeaponDataEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UWeaponDataEnemy : public UWeaponData
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|ShooterParameter")
		float MaxShootDistance = 2;

};
