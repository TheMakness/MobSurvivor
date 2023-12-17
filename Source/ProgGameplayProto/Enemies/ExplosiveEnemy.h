// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ExplosiveEnemy.generated.h"

class USphereComponent;
class APlayerCharacter;

UCLASS()
class PROGGAMEPLAYPROTO_API AExplosiveEnemy : public AEnemy
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = EnemyParameters)
	float ExplosionTriggerDistance;

	UPROPERTY(EditAnywhere, Category = EnemyParameters)
	float MaxExplosionRadius;

	UPROPERTY(EditAnywhere, Category = EnemyParameters)
	float DetonationSpeed;

	UPROPERTY(EditAnywhere, Category = EnemyParameters)
	float InitiateExplosionDelay;

private:
	UPROPERTY(VisibleAnywhere, Export)
	const TObjectPtr<USphereComponent> ExplosionCollider;

	// Calculated radius depending on Explosion Speed over Time
	float LerpAlpha;

	bool bIsInitiatingExplosion = false;
	
	bool bExplode = false;
	
	FTimerHandle InitiatingExplosionTimer;

public:
	// Sets default values for this pawn's properties
	AExplosiveEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Calculate the current radius of the explosion according to given speed and current time
	 * @param DeltaTime DeltaTime from Tick
	 * @return The radius of the explosion from current time and speed
	 */
	float CalculateExplosionRadius(float DeltaTime);

	/**
	 * Prepare explosion
	 */
	void InitiateExplosion();

	/**
	 * Explodes the enemy by changing explosion collider radius, enemy is killed itself at the end.
	 * @param DeltaTime Tick
	 */
	void SelfExplodes(const float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInitiateExplosion"))
	void ReceiveOnInitiateExplosion();
	
private:
	UFUNCTION()
	void MakeDamage(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
};
