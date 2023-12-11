// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BonusData.generated.h"

class UPermanentUpgradeData;
/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class PROGGAMEPLAYPROTO_API UBonusData : public UDataAsset
{
	GENERATED_BODY()

public:
	// Displayed in the UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FText Title;

	// Displayed in the UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FText Description;

	// Image displayed in the UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	TObjectPtr<UTexture2D> Image;

	/**
	 * Apply bonus on the player character
	 */
	UFUNCTION(BlueprintCallable)
	virtual void ApplyOnMainCharacter();
};
