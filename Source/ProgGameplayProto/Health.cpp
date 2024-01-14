// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

#include "GameUtils.h"
#include "Kismet/GameplayStatics.h"
#include "LevelGameState.h"
#include "Weapons/WeaponProjectile.h"

void UHealth::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UHealth::HitByProjectile(AWeaponProjectile* Projectile)
{
	Super::HitByProjectile(Projectile);

	const float damages = Projectile->GetDamages();

	AddHealth(-damages);
}

void UHealth::HitByAttack(float Damages, AActor* Attacker)
{
	// We don't want the attacker to deal damage to itself
	if (Attacker == GetOwner()) return;
	
	AddHealth(-Damages);
}

void UHealth::AddHealth(float Amount)
{
	if (!bCanTakeDamage) return;

	CurrentHealth += Amount;

	OnHealthChanged.Broadcast(CurrentHealth);
	OnHealthChangedWithoutParameters.Broadcast();

	if (CurrentHealth <= 0)
		Die();
}

void UHealth::Die()
{
	OnBeforeHealthDie.Broadcast();

	OnHealthDie.Broadcast();
	ALevelGameState* GameState = Cast<ALevelGameState>(UGameplayStatics::GetGameState(GetWorld()));
	GameState->AddKilledEnemy();
}

float UHealth::GetCurrentHealthPercentage()
{
	float output = CurrentHealth / MaxHealth;

	output = FMath::Clamp(output, 0, 1);

	return output;
}

void UHealth::SetMaxHealth(const float NewMaxHealth)
{
	
	if (CurrentHealth >= MaxHealth)
	{
		MaxHealth = NewMaxHealth;
		CurrentHealth = MaxHealth;
	}
	else
	{
		MaxHealth = NewMaxHealth;
	}
	OnMaxHealthChange.Broadcast();
}
