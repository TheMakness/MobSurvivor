// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponentEnemy.generated.h"


class AWeaponProjectile;
class UWeaponDataEnemy;
class AEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGGAMEPLAYPROTO_API UWeaponComponentEnemy : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponentEnemy();

protected:
	UPROPERTY()
		TObjectPtr<UWeaponDataEnemy> WeaponDataEnemy;
	UPROPERTY()
		TObjectPtr<AEnemy> Enemy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AWeaponProjectile> WeaponProjectileToSpawn;
	float TimeElapsedSinceLastShoot = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Shoot();

	virtual void SpawnProjectile(FVector Direction);

	virtual TArray<FVector> ComputeSpreadDirections();

	virtual float GetShootDelay();
	virtual int32 GetNumberOfProjectiles();
	virtual float GetProjectileSize();
	virtual float GetProjectileRange();
	virtual float GetProjectileSpeed();
	virtual float GetSpread();
	virtual float GetPrecisionRandomAngle();
	virtual float GetDamages();
	virtual float GetPlayerDistanceSquared();
	virtual bool CheckDistance();
	virtual float GetCriticalHitChance();
	virtual float GetCriticalHitDamagesMultiplier();
	virtual float GetRandomShootDelay();
	virtual float GetRandomDistanceOffset();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeWeapon(AEnemy* NewEnemy);

	virtual void TryShooting(float DeltaTime);

	virtual void SetData(UWeaponDataEnemy* Data) { WeaponDataEnemy = Data; }

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
	float BonusCriticalHitChance = 0;
	float BonusCriticalHitChanceMultiplier = 0;
	float BonusCriticalHitDamageMultiplier = 0;
		
};
