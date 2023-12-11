// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PermanentUpgradeData.h"
#include "ProgGameplayProto/Powers/PowerComponent.h"
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
	
	const TSubclassOf<UPowerComponent>& GetComponent() const;

	// Cooldown timer in seconds, that prevent the Use of the Power while it's running. Put 0 to deactivate the cooldown
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<int,float> CooldownTime = { {1,10} };
	
protected:
	// Component holding the Game Logic of the power. The component has a reference to this Data Asset
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPowerComponent> PowerComponent;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Metadata", meta=(DisplayPriority=0))
	TEnumAsByte<EType> Type = EType::Power;
	
	friend bool operator==(const UPowerPUData& Lhs, const UPowerPUData& RHS)
	{
		return static_cast<const UPermanentUpgradeData&>(Lhs) == static_cast<const UPermanentUpgradeData&>(RHS)
			&& Lhs.PowerComponent == RHS.PowerComponent;
	}

	friend bool operator!=(const UPowerPUData& Lhs, const UPowerPUData& RHS)
	{
		return !(Lhs == RHS);
	}
};
