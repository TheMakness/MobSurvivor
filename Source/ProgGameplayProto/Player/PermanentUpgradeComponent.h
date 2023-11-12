// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PermanentUpgradeComponent.generated.h"

class UObjectPermanentUpgrade;
class UEffectPermanentUpgrade;
class UBasePermanentUpgrade;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UPermanentUpgradeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPermanentUpgradeComponent();

	/*void AddUpgrade(UEffectPermanentUpgrade* EffectUpgrade);
	void AddUpgrade(UObjectPermanentUpgrade* EffectUpgrade);

	void RemoveUpgrade(UEffectPermanentUpgrade* EffectUpgrade);
	void RemoveUpgrade(UObjectPermanentUpgrade* EffectUpgrade);*/
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// List of unlocked upgrades
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	TArray<TSubclassOf<UEffectPermanentUpgrade>> ActiveEffectUpgrades;

	TArray<UEffectPermanentUpgrade*> InstantiatedEffectUpgrades;
};
