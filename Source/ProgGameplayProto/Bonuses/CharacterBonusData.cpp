// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBonusData.h"

#include "ProgGameplayProto/Health.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"
#include "ProgGameplayProto/ExperienceComponent.h"
#include "ProgGameplayProto/GoldComponent.h"

void UCharacterBonusData::ApplyOnMainCharacter()
{
	const APlayerCharacter* MainCharacter = UGameUtils::GetMainCharacter();
	if (!IsValid(MainCharacter)) return;

	Apply(MainCharacter);
}

void UCharacterBonusData::Apply(const APlayerCharacter* Character) const
{
	UHealth* HealthComponent = Character->GetHealth();
	if (IsValid(HealthComponent))
	{
		HealthComponent->AddHealth(HealAmount);
	}
	
	UExperienceComponent* ExperienceComponent = Character->GetExperience();
	if (IsValid(ExperienceComponent))
	{
		ExperienceComponent->IncrementExperienceMultiplier(ExperienceMultiplierIncrement);
	}
	
	UGoldComponent* GoldComponent = Character->GetGold();
	if (IsValid(GoldComponent))
	{
		GoldComponent->IncrementGoldMultiplier(GoldMultiplierIncrement);
	}
}
