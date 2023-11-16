// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ShooterEnemy.generated.h"

class UWeaponDataEnemy;
class UWeaponComponentEnemy;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AShooterEnemy : public AEnemy
{
	GENERATED_BODY()
public:
	AShooterEnemy();
protected:
		virtual void BeginPlay() override;
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
			UWeaponComponentEnemy* Weapon;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponData)
			UWeaponDataEnemy* DefaultWeaponData;

public:
	void SetupDefaultWeapon();
	bool WantsToShoot();
};
