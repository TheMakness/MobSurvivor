// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"

#include "ProgGameplayProto/Weapons/WeaponComponentEnemy.h"

 AShooterEnemy::AShooterEnemy()
{
	 Weapon = CreateDefaultSubobject<UWeaponComponentEnemy>("Weapon");
}

 void AShooterEnemy::BeginPlay()
 {
	 Super::BeginPlay();
	 SetupDefaultWeapon();
 }

void AShooterEnemy::SetupDefaultWeapon()
{
	Weapon->InitializeWeapon(this);
	Weapon->SetData(DefaultWeaponData);
}

bool AShooterEnemy::WantsToShoot()
{
	return false;
}
