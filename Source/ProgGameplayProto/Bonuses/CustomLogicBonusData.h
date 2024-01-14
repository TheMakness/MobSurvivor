// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusData.h"
#include "Templates/SubclassOfField.h"
#include "CustomLogicBonusData.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UCustomLogicBonusData : public UBonusData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> CustomLogicActor;
	
	virtual void ApplyOnMainCharacter() override;
};
