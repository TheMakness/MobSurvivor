// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PermanentUpgradeComponent_Base.h"
#include "KnockbackBlastComponent.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROGGAMEPLAYPROTO_API UKnockbackBlastComponent : public UPermanentUpgradeComponent_Base
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float ZoneSize = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Force = 100;

	

private:
	UPROPERTY()
	AActor* LastActorHit;

	UFUNCTION()
		void CheckCollision();

	

};
