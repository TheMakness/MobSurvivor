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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health Bonus")
	int HealAmount = 0;

	virtual void ApplyOnMainCharacter() override;

	void Apply(const APlayerCharacter* Character) const;
};
