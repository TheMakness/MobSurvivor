// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "ProgGameplayProto/Weapons/WeaponData.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"
#include "ProgGameplayProto/Weapons/WeaponProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/MobSurvivorInstance.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"
#include "ProgGameplayProto/PermanentUpgrades/PermanentUpgrade.h"
#include "ProgGameplayProto/PermanentUpgrades/UUpgradesUtils.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TryShooting(DeltaTime);
}

void UWeaponComponent::InitializeWeapon(APlayerCharacter* NewCharacter)
{
	Character = NewCharacter;
}

void UWeaponComponent::TryShooting(float DeltaTime)
{
	TimeElapsedSinceLastShoot += DeltaTime;

	if (!IsValid(Character)) return;

	if (!Character->WantsToShoot()) return;

	if (TimeElapsedSinceLastShoot >= GetShootDelay())
	{
		Shoot();
	}
}

void UWeaponComponent::SetData(UWeaponData* Data)
{
	WeaponData = Data;

	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (IsValid(GI))
	{
		TArray<FPermanentUpgrade> Upgrades = GI->GetUpgrades();
		UPermanentUpgradeData* UpgradeData = Cast<UPermanentUpgradeData>(WeaponData);

		FPermanentUpgrade* FoundUpgrade = Upgrades.FindByPredicate([UpgradeData](const FPermanentUpgrade& Item) -> bool
		{
			return Item.Data == UpgradeData;
		});

		CurrentWeaponLevel = FoundUpgrade->CurrentLevel;
	}
}

void UWeaponComponent::AddEffect(UProjectileEffect* Effect)
{
	Effects.Add(Effect);
}


void UWeaponComponent::Shoot()
{
	TimeElapsedSinceLastShoot = 0;

	if (!IsValid(Character)) return;
	if (!IsValid(Character->WeaponProjectileToSpawn)) return;

	TArray<FVector> shootDirections = ComputeSpreadDirections();

	for (int i = 0; i < shootDirections.Num(); i++)
	{
		SpawnProjectile(shootDirections[i]);
	}
}

void UWeaponComponent::SpawnProjectile(FVector Direction)
{
	const FVector spawnLocation = Character->GetActorLocation();
	const FRotator spawnRotation = FRotator::ZeroRotator;

	AWeaponProjectile* projectile = Character->GetWorld()->SpawnActor<AWeaponProjectile>(
		Character->WeaponProjectileToSpawn, spawnLocation, spawnRotation);

	projectile->SetParameters(ProjectileOwner::Player, GetProjectileSize(), GetProjectileRange(), GetProjectileSpeed(),
	                          GetProjectileStunTime(), GetDamages(), GetCriticalHitChance(),
	                          GetCriticalHitDamagesMultiplier(), GetKnockbackForce());

	if (Direction == FVector::ZeroVector)
		Direction = Character->GetActorForwardVector();
	projectile->SetDirection(Direction);

	for (int i = 0; i < Effects.Num(); i++)
	{
		Effects[i]->RegisterProjectile(projectile);
	}
}

FVector UWeaponComponent::GetMouseDirection()
{
	FVector mouseLocation;
	FVector mouseDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	FHitResult outHit;
	FVector endTraceLocation = mouseLocation + mouseDirection * 10000;
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(ECC_WorldStatic);
	GetWorld()->LineTraceSingleByObjectType(outHit, mouseLocation, endTraceLocation, params);

	if (outHit.bBlockingHit)
	{
		FVector neutralCharacterLocation = Character->GetActorLocation();
		neutralCharacterLocation.Z = 0;
		FVector neutralMouseLocation = outHit.Location;
		neutralMouseLocation.Z = 0;

		FVector direction = neutralMouseLocation - neutralCharacterLocation;
		direction.Normalize();

		return direction;
	}

	return Character->GetActorForwardVector();
}

TArray<FVector> UWeaponComponent::ComputeSpreadDirections()
{
	TArray<FVector> directions;

	FVector centralDirection = GetMouseDirection();
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

int32 UWeaponComponent::GetNumberOfProjectiles()
{
	if (!IsValid(WeaponData)) return int32();

	const int StatLevel = UUpgradesUtils::GetStatLevel(WeaponData->NumberOfShots, CurrentWeaponLevel);


	int32 output = static_cast<int32>(WeaponData->NumberOfShots[StatLevel] + BonusNumberOfShots) * (WeaponData->
		NumberOfShotsMultiplier[StatLevel] + BonusNumberOfShotsMultiplier);
	output = FMath::Max(0, output);

	return output;
}

float UWeaponComponent::GetShootDelay()
{
	if (!IsValid(WeaponData)) return 0.0f;


	float value = FMath::Max(
		0.1f, (WeaponData->FireRate[UUpgradesUtils::GetStatLevel(WeaponData->FireRate, CurrentWeaponLevel)] +
			BonusFireRate));
	float multiplier = FMath::Max(
		0.1f, WeaponData->FireRateMultiplier[UUpgradesUtils::GetStatLevel(
			WeaponData->FireRateMultiplier, CurrentWeaponLevel)] + BonusFireRateMultiplier);

	return 1 / (value * multiplier);
}

float UWeaponComponent::GetProjectileSize()
{
	if (!IsValid(WeaponData)) return 0.0f;


	float value = FMath::Max(
		0.1f, WeaponData->ProjectileSize[UUpgradesUtils::GetStatLevel(WeaponData->ProjectileSize, CurrentWeaponLevel)] +
		BonusProjectileSize);
	float multiplier = FMath::Max(
		0.1f, WeaponData->ProjectileSizeMultiplier[UUpgradesUtils::GetStatLevel(
			WeaponData->ProjectileSizeMultiplier, CurrentWeaponLevel)] + BonusProjectileSizeMultiplier);

	return value * multiplier;
}

float UWeaponComponent::GetProjectileRange()
{
	if (!IsValid(WeaponData)) return 0.0f;


	float value = FMath::Max(
		100, WeaponData->Range[UUpgradesUtils::GetStatLevel(WeaponData->Range, CurrentWeaponLevel)] + BonusRange);
	float multiplier = FMath::Max(
		0.1f, WeaponData->RangeMultiplier[UUpgradesUtils::GetStatLevel(WeaponData->RangeMultiplier, CurrentWeaponLevel)]
		+ BonusRangeMultiplier);

	float output = FMath::Max(100, value * multiplier);

	return output;
}

float UWeaponComponent::GetProjectileSpeed()
{
	if (!IsValid(WeaponData)) return 0.0f;


	float value = FMath::Max(
		50, WeaponData->ProjectileSpeed[UUpgradesUtils::GetStatLevel(WeaponData->ProjectileSpeed, CurrentWeaponLevel)] +
		BonusProjectileSpeed);
	float multiplier = FMath::Max(
		0.1f, WeaponData->ProjectileSpeedMultiplier[UUpgradesUtils::GetStatLevel(
			WeaponData->ProjectileSpeedMultiplier, CurrentWeaponLevel)] + BonusProjectileSpeedMultiplier);

	float output = FMath::Max(50, value * multiplier);

	return output;
}

float UWeaponComponent::GetProjectileStunTime()
{
	if (!IsValid(WeaponData)) return 0.0f;


	float value = WeaponData->ProjectileStunTime[UUpgradesUtils::GetStatLevel(
		WeaponData->ProjectileStunTime, CurrentWeaponLevel)] + BonusProjectileStunTime;
	float multiplier = FMath::Max(
		0.1f, WeaponData->ProjectileStunTimeMultiplier[UUpgradesUtils::GetStatLevel(
			WeaponData->ProjectileStunTimeMultiplier, CurrentWeaponLevel)] + BonusProjectileStunTimeMultiplier);
	float output = value * multiplier;

	return output;
}

float UWeaponComponent::GetSpread()
{
	if (!IsValid(WeaponData)) return 0.0f;


	return (WeaponData->Spread[UUpgradesUtils::GetStatLevel(WeaponData->Spread, CurrentWeaponLevel)] + BonusSpread) * (
		WeaponData->SpreadMultiplier[UUpgradesUtils::GetStatLevel(WeaponData->SpreadMultiplier, CurrentWeaponLevel)] +
		BonusSpreadMultiplier);
}

float UWeaponComponent::GetPrecisionRandomAngle()
{
	if (!IsValid(WeaponData)) return 0.0f;


	const float totalPrecision = (WeaponData->Precision[
		UUpgradesUtils::GetStatLevel(WeaponData->Precision, CurrentWeaponLevel)] + BonusPrecision) * (WeaponData->
		PrecisionMultiplier[UUpgradesUtils::GetStatLevel(WeaponData->PrecisionMultiplier, CurrentWeaponLevel)] +
		BonusPrecisionMultiplier);

	const float precisionFactor = FMath::Clamp((1 - totalPrecision), 0, 1);
	const float angleLimit = 30 * precisionFactor;

	const float angle = FMath::RandRange(-angleLimit, angleLimit);

	return angle;
}

float UWeaponComponent::GetDamages()
{
	if (!IsValid(WeaponData)) return 0.0f;

	float Output = (WeaponData->Damages[UUpgradesUtils::GetStatLevel(WeaponData->Damages, CurrentWeaponLevel)] +
		BonusDamages) * (WeaponData->DamagesMultiplier[UUpgradesUtils::GetStatLevel(
		WeaponData->DamagesMultiplier, CurrentWeaponLevel)] + BonusDamagesMultiplier);
	Output = FMath::Max(0.1f, Output);

	return Output;
}

float UWeaponComponent::GetCriticalHitChance()
{
	if (!IsValid(WeaponData)) return 0.0f;

	return (WeaponData->CriticalHitChance[
		UUpgradesUtils::GetStatLevel(WeaponData->CriticalHitChance, CurrentWeaponLevel)] + BonusCriticalHitChance) * (
		WeaponData->CriticalHitChanceMultiplier[UUpgradesUtils::GetStatLevel(
			WeaponData->CriticalHitChanceMultiplier, CurrentWeaponLevel)] + BonusCriticalHitChanceMultiplier);
}

float UWeaponComponent::GetCriticalHitDamagesMultiplier()
{
	if (!IsValid(WeaponData)) return 0.0f;


	float Output = WeaponData->CriticalHitDamageMultiplier[UUpgradesUtils::GetStatLevel(
		WeaponData->CriticalHitDamageMultiplier, CurrentWeaponLevel)] + BonusCriticalHitDamageMultiplier;
	Output = FMath::Max(1, Output);

	return Output;
}

float UWeaponComponent::GetKnockbackForce()
{
	if (!IsValid(WeaponData)) return 0.0f;

	return WeaponData->KnockbackForce[UUpgradesUtils::GetStatLevel(WeaponData->KnockbackForce, CurrentWeaponLevel)] +
		BonusKnockbackForce;
}
