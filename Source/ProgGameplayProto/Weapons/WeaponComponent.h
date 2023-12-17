// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class UProjectileEffect;
class UWeaponData;
class APlayerCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	float BonusFireRate = 0;
	float BonusFireRateMultiplier = 0;
	float BonusNumberOfShots = 0;
	float BonusNumberOfShotsMultiplier = 0;
	float BonusPrecision = 0;
	float BonusPrecisionMultiplier = 0;
	float BonusSpread = 0;
	float BonusSpreadMultiplier = 0;
	float BonusDamages = 0;
	float BonusDamagesMultiplier = 0;
	float BonusProjectileSize = 0;
	float BonusProjectileSizeMultiplier = 0;
	float BonusRange = 0;
	float BonusRangeMultiplier = 0;
	float BonusProjectileSpeed = 0;
	float BonusProjectileSpeedMultiplier = 0;
	float BonusProjectileStunTime = 0;
	float BonusProjectileStunTimeMultiplier = 0;
	float BonusCriticalHitChance = 0;
	float BonusCriticalHitChanceMultiplier = 0;
	float BonusCriticalHitDamageMultiplier = 0;
	
	float BonusKnockbackForce = 0;

protected:
	UPROPERTY()
	TObjectPtr<UWeaponData> WeaponData;

	UPROPERTY()
	int CurrentWeaponLevel = 1;

	UPROPERTY()
	TObjectPtr<APlayerCharacter> Character;

	UPROPERTY()
	TArray<UProjectileEffect*> Effects;

	float TimeElapsedSinceLastShoot = 0;

public:
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

	virtual void Shoot();

	virtual void SpawnProjectile(FVector Direction);

	virtual FVector GetMouseDirection();

	virtual TArray<FVector> ComputeSpreadDirections();

	virtual float GetShootDelay();
	virtual int32 GetNumberOfProjectiles();
	virtual float GetProjectileSize();
	virtual float GetProjectileRange();
	virtual float GetProjectileSpeed();
	virtual float GetProjectileStunTime();
	virtual float GetSpread();
	virtual float GetPrecisionRandomAngle();
	virtual float GetDamages();
	virtual float GetCriticalHitChance();
	virtual float GetCriticalHitDamagesMultiplier();

	virtual float GetKnockbackForce();
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeWeapon(APlayerCharacter* NewCharacter);

	virtual void TryShooting(float DeltaTime);

	virtual void SetData(UWeaponData* Data);

	virtual void AddEffect(UProjectileEffect* Effect);
};
