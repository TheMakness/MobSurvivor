// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBonusData.h"
#include "BounceBonusData.generated.h"

class UWeaponComponent;
class APlayerCharacter;
class UBounceEffect;

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UBounceBonusData : public UWeaponBonusData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBounceEffect> BounceEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfBounces;

public:
	virtual void Apply(APlayerCharacter* Character, UWeaponComponent* Weapon) override;
};
