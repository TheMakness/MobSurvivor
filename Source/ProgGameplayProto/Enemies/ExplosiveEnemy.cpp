// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveEnemy.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/Health.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"

// Sets default values
AExplosiveEnemy::AExplosiveEnemy():


	ExplosionTriggerDistance(0),
	MaxExplosionRadius(0),
	DetonationSpeed(0),
	ExplosionCollider(CreateDefaultSubobject<USphereComponent>("Explosion Collider")),
	LerpAlpha(0)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ExplosionCollider->SetupAttachment(Collision);
	ExplosionCollider->SetSphereRadius(0);
}

// Called when the game starts or when spawned
void AExplosiveEnemy::BeginPlay()
{
	Super::BeginPlay();


	ExplosionCollider->OnComponentBeginOverlap.AddDynamic(this, &AExplosiveEnemy::MakeDamage);
}

// Called every frame
void AExplosiveEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsInitiatingExplosion)
	{
		const auto Player = UGameUtils::GetMainCharacter();

		if (!IsValid(Player)) return;

		const auto PlayerLocation = Player->GetTransform().GetLocation();

		const float DistanceFromPlayer = FVector::Distance(GetTransform().GetLocation(), PlayerLocation);

		if (DistanceFromPlayer < ExplosionTriggerDistance)
		{
			InitiateExplosion();
		}
	}

	if (bExplode)
	{
		SelfExplodes(DeltaTime);
	}
}

float AExplosiveEnemy::CalculateExplosionRadius(float DeltaTime)
{
	LerpAlpha += (DetonationSpeed * DeltaTime) / 100;
	const auto Radius = FMath::Lerp(0, MaxExplosionRadius, LerpAlpha);

	if (LerpAlpha >= 1.0f)
	{
		LerpAlpha = 0;
	}

	return Radius;
}

void AExplosiveEnemy::InitiateExplosion()
{
	bCanMove = false;
	bIsInitiatingExplosion = true;

	ReceiveOnInitiateExplosion();

	GetWorld()->GetTimerManager().SetTimer(InitiatingExplosionTimer, [&]()
	{
		bExplode = true;
	}, InitiateExplosionDelay, false);
}

void AExplosiveEnemy::SelfExplodes(const float DeltaTime)
{
	const auto Radius = CalculateExplosionRadius(DeltaTime);
	ExplosionCollider->SetSphereRadius(Radius);

	// When explosion finished, we can kill it
	if (Radius >= MaxExplosionRadius)
	{
		Die();
	}
}

// Called to bind functionality to input
void AExplosiveEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AExplosiveEnemy::MakeDamage(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
                                 UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg,
                                 const FHitResult& HitResult)
{
	const auto HealthComponent = Actor->GetComponentByClass<UHealth>();

	if (IsValid(HealthComponent))
	{
		HealthComponent->HitByAttack(Damages, this);
	}
}
