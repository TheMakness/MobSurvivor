// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileHitEffect.h"
#include "BounceEffect.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UBounceEffect : public UProjectileHitEffect
{
	GENERATED_BODY()

public:
	int32 NumberOfAdditionalBounces;

public:
	virtual void RegisterProjectile(AWeaponProjectile* Projectile) override;

	virtual void OnProjectileHit(AWeaponProjectile* Projectile, FVector HitLocation, FVector OriginLocation) override;
};
