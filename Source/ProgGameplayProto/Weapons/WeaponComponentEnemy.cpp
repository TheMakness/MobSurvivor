// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponentEnemy.h"

#include "WeaponDataEnemy.h"
#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/Enemies/Enemy.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"
#include "ProgGameplayProto/Weapons//WeaponProjectile.h"

// Sets default values for this component's properties
UWeaponComponentEnemy::UWeaponComponentEnemy()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponentEnemy::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponComponentEnemy::Shoot()
{
	TimeElapsedSinceLastShoot = 0;
	if (!WeaponProjectileToSpawn) return;

	TArray<FVector> shootDirections = ComputeSpreadDirections();

	for (int i = 0; i < shootDirections.Num(); i++)
	{
		SpawnProjectile(shootDirections[i]);
	}
}

void UWeaponComponentEnemy::SpawnProjectile(FVector Direction)
{
	const FVector spawnLocation = Enemy->GetActorLocation();
	const FRotator spawnRotation = FRotator::ZeroRotator;
	AWeaponProjectile* projectile = Enemy->GetWorld()->SpawnActor<AWeaponProjectile>(WeaponProjectileToSpawn,spawnLocation, spawnRotation);

	projectile->SetParameters(ProjectileOwner::Enemy,GetProjectileSize(), GetProjectileRange(), GetProjectileSpeed(), GetDamages(), GetCriticalHitChance(), GetCriticalHitDamagesMultiplier());
	projectile->SetDirection(Direction);

}

TArray<FVector> UWeaponComponentEnemy::ComputeSpreadDirections()
{
	TArray<FVector> directions;

	FVector centralDirection = UGameUtils::GetMainCharacter()->GetActorLocation() - GetOwner()->GetActorLocation();
	centralDirection.Normalize();
	const int32 numberOfProjectiles = GetNumberOfProjectiles();

	if (numberOfProjectiles < 2)
	{
		centralDirection = centralDirection.RotateAngleAxis(GetPrecisionRandomAngle(), FVector::UpVector);
		directions.Add(centralDirection);
	}
	else
	{
		const float angleIncrement = GetSpread() / (numberOfProjectiles - 1);
		const float spread = GetSpread();

		for (int i = 0; i < numberOfProjectiles; i++)
		{
			float offsetAngle = (i * angleIncrement) - (spread / 2.0f);
			offsetAngle += GetPrecisionRandomAngle();
			FVector direction = centralDirection;
			direction = direction.RotateAngleAxis(offsetAngle, FVector::UpVector);

			directions.Add(direction);
		}
	}

	return directions;
}

float UWeaponComponentEnemy::GetShootDelay()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	float value = FMath::Max(0.1f, (WeaponDataEnemy->FireRate + BonusFireRate));
	float multiplier = FMath::Max(0.1f, WeaponDataEnemy->FireRateMultiplier + BonusFireRateMultiplier);

	return 1 / (value * multiplier);
}

int32 UWeaponComponentEnemy::GetNumberOfProjectiles()
{
	if (!IsValid(WeaponDataEnemy)) return int32();

	int32 output = static_cast<int32>(WeaponDataEnemy->NumberOfShots + BonusNumberOfShots) * (WeaponDataEnemy->NumberOfShotsMultiplier + BonusNumberOfShotsMultiplier);
	output = FMath::Max(0, output);

	return output;
}

float UWeaponComponentEnemy::GetProjectileSize()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	float value = FMath::Max(0.1f, WeaponDataEnemy->ProjectileSize + BonusProjectileSize);
	float multiplier = FMath::Max(0.1f, WeaponDataEnemy->ProjectileSizeMultiplier + BonusProjectileSizeMultiplier);

	return value * multiplier;
}

float UWeaponComponentEnemy::GetProjectileRange()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	float value = FMath::Max(100, WeaponDataEnemy->Range + BonusRange);
	float multiplier = FMath::Max(0.1f, WeaponDataEnemy->RangeMultiplier + BonusRangeMultiplier);

	float output = FMath::Max(100, value * multiplier);

	return output;
}


float UWeaponComponentEnemy::GetProjectileSpeed()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	float value = FMath::Max(50, WeaponDataEnemy->ProjectileSpeed + BonusProjectileSpeed);
	float multiplier = FMath::Max(0.1f, WeaponDataEnemy->ProjectileSpeedMultiplier + BonusProjectileSpeedMultiplier);

	float output = FMath::Max(50, value * multiplier);

	return output;
}

float UWeaponComponentEnemy::GetSpread()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	return (WeaponDataEnemy->Spread + BonusSpread) * (WeaponDataEnemy->SpreadMultiplier + BonusSpreadMultiplier);
}

float UWeaponComponentEnemy::GetPrecisionRandomAngle()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	const float totalPrecision = (WeaponDataEnemy->Precision + BonusPrecision) * (WeaponDataEnemy->PrecisionMultiplier + BonusPrecisionMultiplier);

	const float precisionFactor = FMath::Clamp((1 - totalPrecision), 0, 1);
	const float angleLimit = 30 * precisionFactor;

	const float angle = FMath::RandRange(-angleLimit, angleLimit);

	return angle;
}

float UWeaponComponentEnemy::GetDamages()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	float output = (WeaponDataEnemy->Damages + BonusDamages) * (WeaponDataEnemy->DamagesMultiplier + BonusDamagesMultiplier);
	output = FMath::Max(0.1f, output);

	return output;
}

float UWeaponComponentEnemy::GetPlayerDistanceSquared()
{
	return FVector::DistSquared2D(UGameUtils::GetMainCharacter()->GetActorLocation(), GetOwner()->GetActorLocation());
}

bool UWeaponComponentEnemy::CheckDistance()
{
	return GetPlayerDistanceSquared() < (WeaponDataEnemy->MaxShootDistance) * (WeaponDataEnemy->MaxShootDistance) - GetRandomDistanceOffset() * GetRandomDistanceOffset();
}

float UWeaponComponentEnemy::GetCriticalHitChance()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	return (WeaponDataEnemy->CriticalHitChance + BonusCriticalHitChance) * (WeaponDataEnemy->CriticalHitChanceMultiplier + BonusCriticalHitChanceMultiplier);
}

float UWeaponComponentEnemy::GetCriticalHitDamagesMultiplier()
{
	if (!IsValid(WeaponDataEnemy)) return 0.0f;

	float output = WeaponDataEnemy->CriticalHitDamageMultiplier + BonusCriticalHitDamageMultiplier;
	output = FMath::Max(1, output);

	return output;
}

float UWeaponComponentEnemy::GetRandomShootDelay()
{
	return FMath::RandRange(WeaponDataEnemy->RandomOffsetDelay.X, WeaponDataEnemy->RandomOffsetDelay.Y);
}

float UWeaponComponentEnemy::GetRandomDistanceOffset()
{
	return FMath::RandRange(WeaponDataEnemy->RandomOffsetDistance.X, WeaponDataEnemy->RandomOffsetDistance.Y);
}




// Called every frame
void UWeaponComponentEnemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TryShooting(DeltaTime);
	// ...
}

void UWeaponComponentEnemy::InitializeWeapon(AEnemy* NewEnemy)
{
	Enemy = NewEnemy;
}

void UWeaponComponentEnemy::TryShooting(float DeltaTime)
{
	TimeElapsedSinceLastShoot += DeltaTime;
	if(!WeaponDataEnemy) return;
	if(!CheckDistance()) return;
	if (TimeElapsedSinceLastShoot >= GetShootDelay() + GetRandomShootDelay())
	{
		Shoot();
	}

}

