// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/Health.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"
#include "ProgGameplayProto/Drops/EnemyDropperComponent.h"
#include "ProgGameplayProto/Weapons/WeaponProjectile.h"

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

	Health->OnHitByProjectile.AddDynamic(this, &AEnemy::CancelVelocity);
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

	AddActorWorldOffset(movement);
}

void AEnemy::Die()
{
	Destroy();
}


void AEnemy::CancelVelocity(AWeaponProjectile* Projectile)
{
	if(Projectile->GetStunTime() <= 0) return;

	bCanMove = false;
	GetWorld()->GetTimerManager().SetTimer(CanMoveTimerHandle, [&]()->void
		{
			bCanMove = true;
		}, Projectile->GetStunTime(), false);
	
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


