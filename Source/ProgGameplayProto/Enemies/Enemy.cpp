// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/Health.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"
#include "ProgGameplayProto/Drops/EnemyDropperComponent.h"
#include "ProgGameplayProto/Weapons/WeaponProjectile.h"
#include "ProgGameplayProto/KnockbackComponent.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanMove = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	SetRootComponent(Collision);

	Health = CreateDefaultSubobject<UHealth>("Health");

	Dropper = CreateDefaultSubobject<UEnemyDropperComponent>("Dropper");
	Dropper->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Health->OnHealthDie.AddDynamic(this, &AEnemy::Die);

	Health->OnHitByProjectile.AddDynamic(this, &AEnemy::HitByProjectile);
}

void AEnemy::MoveTowardPlayer(float DeltaTime)
{
	if (!bCanMove) return;

	const APlayerCharacter* player = UGameUtils::GetMainCharacter();

	if (!IsValid(player)) return;

	FVector direction = player->GetActorLocation() - GetActorLocation();
	direction.Z = 0;
	direction.Normalize();

	FVector movement = direction * MoveSpeed * DeltaTime;

	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(player->GetActorLocation(), GetActorLocation());

	SetActorRotation(Rotation);
	AddActorWorldOffset(movement);
}

void AEnemy::Die()
{
	Destroy();
}

void AEnemy::Knockback(AWeaponProjectile* Projectile)
{
	const auto KnockbackComponent = this->GetComponentByClass<UKnockbackComponent>();
	if (IsValid(KnockbackComponent))
	{
		FVector Direction = GetActorForwardVector();
		Direction.Z = 0;
		Direction.Normalize();

		KnockbackComponent->Knockback(Projectile->GetKnockbackForce(), Direction);
	}
}

void AEnemy::HitByProjectile(AWeaponProjectile* Projectile)
{
	ReceiveOnHitByProjectile(Projectile);
	
	if (Projectile->GetKnockbackForce() > 0)
	{
		Knockback(Projectile);

		if (Projectile->GetStunTime() > 0)
		{
			const auto KnockbackComponent = this->GetComponentByClass<UKnockbackComponent>();
			if (IsValid(KnockbackComponent))
			{
				FTimerDelegate Delegate;
				Delegate.BindUObject(this, &AEnemy::CancelVelocity, Projectile->GetStunTime());

				GetWorld()->GetTimerManager().SetTimer(KnockbackTimer, Delegate, KnockbackComponent->Duration, false);
			}
		}
	}
	else
	{
		if (Projectile->GetStunTime() > 0)
		{
			CancelVelocity(Projectile->GetStunTime());
		}
	}
}


void AEnemy::CancelVelocity(float StunTime)
{
	
	if (StunTime <= 0) return;

	bCanMove = false;
	GetWorld()->GetTimerManager().SetTimer(CanMoveTimerHandle, [&]()-> void
	{
		bCanMove = true;
	}, StunTime, false);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTowardPlayer(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::TryAttacking(AActor* Target)
{
	if (!Target->IsA(APlayerCharacter::StaticClass())) return;

	UHealth* targetHealth = Target->FindComponentByClass<UHealth>();

	if (!IsValid(targetHealth)) return;

	targetHealth->HitByAttack(Damages, this);

	Attack_BP(Target);
}

void AEnemy::SwitchCanMove()
{
	bCanMove = !bCanMove;
}
