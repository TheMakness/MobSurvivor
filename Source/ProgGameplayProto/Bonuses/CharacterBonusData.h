// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusData.h"
#include "ProgGameplayProto/GameUtils.h"
#include "CharacterBonusData.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UCharacterBonusData : public UBonusData
{
	GENERATED_BODY()

public:
	// One-shot heal bonus
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Bonus")
	int HealAmount = 0;

	// Multiply the experience gain of the character for each orb collected (this increment the multiplier of the experience component, be careful not to put something too big!)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Bonus")
	float ExperienceMultiplierIncrement = 0;

	// Multiply the gold gain of the character (this increment the multiplier of the gold component, be careful not to put something too big!)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Bonus")
	float GoldMultiplierIncrement = 0;

	virtual void ApplyOnMainCharacter() override;

	void Apply(const APlayerCharacter* Character) const;
};
