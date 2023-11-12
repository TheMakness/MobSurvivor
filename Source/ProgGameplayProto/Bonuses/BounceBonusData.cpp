// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceBonusData.h"
#include "ProgGameplayProto/Effects/BounceEffect.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"

void UBounceBonusData::Apply(APlayerCharacter* Character, UWeaponComponent* Weapon)
{
	Super::Apply(Character, Weapon);

	UBounceEffect* effect = NewObject<UBounceEffect>(this, BounceEffect);
	effect->NumberOfAdditionalBounces = NumberOfBounces;

	Weapon->AddEffect(effect);
}