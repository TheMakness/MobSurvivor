// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PermanentUpgradeData.h"
#include "ProgGameplayProto/Powers/Power.h"
#include "PowerPUData.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UPowerPUData : public UPermanentUpgradeData
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual EType GetType() const override
	{
		return Type;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APower> PowerImplementation;

	
private:
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EType> Type = EType::Power;
	
	friend bool operator==(const UPowerPUData& Lhs, const UPowerPUData& RHS)
	{
		return static_cast<const UPermanentUpgradeData&>(Lhs) == static_cast<const UPermanentUpgradeData&>(RHS)
			&& Lhs.PowerImplementation == RHS.PowerImplementation;
	}

	friend bool operator!=(const UPowerPUData& Lhs, const UPowerPUData& RHS)
	{
		return !(Lhs == RHS);
	}
};
