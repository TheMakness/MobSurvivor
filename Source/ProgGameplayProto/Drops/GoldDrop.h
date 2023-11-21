// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drop.h"
#include "GoldDrop.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AGoldDrop : public ADrop
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GoldAmount;

protected:
	virtual void Collect() override;

};
